/*
 * generalHardware.cpp
 *
 * Created: 02/10/2018 16:37:18
 *  Author: Conrad
 */


#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#include <stdlib.h>

#include "hardware.h"


void hardwareSetup() {
    cli();

    timerSetup();
    TLCSetup();

    // indicator led, output, high
    DDRD |= 1u << (unsigned) LED;
    PORTD |= 1u << (unsigned) LED;

    // IR receiver - INT0 falling edge interrupt
    EICRA |= 1u << (unsigned) ISC01;    // configure INT0 falling edge interrupt
    EIMSK |= 1u << (unsigned) INT0;        // enable the INT0 external interrupt

    // switch1 - tristate (Hi-Z), external interrupt on any edge
    DDRB |= 0u << (unsigned) SW;
    PORTB |= 1u << (unsigned) SW;
    EICRA |= 1u << (unsigned) ISC20;
    EIMSK |= 1u << (unsigned) INT2;

    // random setup
    uint8_t number = eeprom_read_byte((uint8_t *) 4);
    srand(number++);
    eeprom_write_byte((uint8_t *) 4, number);

    sei();    // enable interrupt globally
}

// INT0: IR-receiver
static volatile uint32_t previousTicks = 0;
static volatile uint8_t pulseCount = 0;
static volatile uint32_t bitPattern = 0;
static volatile uint8_t newKey = 0;


ISR(INT0_vect, ISR_NOBLOCK) {
    uint32_t tempTicks = getTimerTick();    // 1 tick = 0.0512ms
    uint32_t counterTicks = tempTicks - previousTicks;
    previousTicks = tempTicks;
    if (counterTicks >= 500) {    // start of frame (25ms)
        pulseCount = 1;
        bitPattern = 0;
        return;
    }
    if (pulseCount == 1) {
        // indicates start of frame
        // time should be between 11.5 ms and 15.3 ms (ideal: 13.5ms)
        if (counterTicks >= 224 && counterTicks <= 298)
            pulseCount = 2;
        return;
    }
    if (pulseCount >= 2) {
        bitPattern <<= 1u;
        if (counterTicks >= 32)    // logical one are longer than 33 ticks
            bitPattern |= 1u;
        if (pulseCount >= 33) {    // marks end of message
            newKey = 1;
            pulseCount = 0;

            if (bitPattern == 0xF740BF) {    // IR-transmitter: off
                PIND |= 1u << (unsigned) LED;    // toggle status led
            }
            return;
        }
        pulseCount++;
        return;
    }
}

// INT2: button
static volatile uint32_t int2Ticks = 0;
static volatile bool int2FallingEdge = true;

ISR (INT2_vect, ISR_NOBLOCK) {
    if (getTimerTick() <= int2Ticks)    // check for debounce
        return;

    int2Ticks = getTimerTick() + 500;  // 25.5 ms - max debounce time

    if (int2FallingEdge) {
        // code to be executed
        PIND |= 1u << (unsigned) LED;    // toggle Status LED
    }
    int2FallingEdge = !int2FallingEdge;
}
