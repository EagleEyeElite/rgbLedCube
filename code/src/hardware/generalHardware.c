/*
 * generalHardware.cpp
 *
 * Created: 02/10/2018 16:37:18
 *  Author: Conrad
 */


#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "hardware.h"
#include "irCodes.h"
#include "led.h"
#include "reset.h"

_Noreturn static void reset();

static volatile uint8_t __attribute__((section (".noinit"))) software_seed;
static volatile bool softwareReset __attribute__((section (".noinit")));


void hardwareSetup() {
    cli();

    timerSetup();
    TLCSetup();
    initLed();

    // IR receiver - INT0 falling edge interrupt
    EICRA |= 1u << (unsigned) ISC01;    // configure INT0 falling edge interrupt
    EIMSK |= 1u << (unsigned) INT0;        // enable the INT0 external interrupt

    // switch1 - tristate (Hi-Z), external interrupt on any edge
    DDRB |= 0u << (unsigned) SW;
    PORTB |= 1u << (unsigned) SW;
    EICRA |= 1u << (unsigned) ISC20;
    EIMSK |= 1u << (unsigned) INT2;

    // random setup
    if(softwareReset) {
        software_seed++;
    } else {
        software_seed = 0;
    }
    softwareReset = false;

    //uint8_t number = eeprom_read_byte((uint8_t *) 4);
    srand(software_seed);
    //eeprom_write_byte((uint8_t *) 4, number);

    sei();    // enable interrupt globally
}

// INT0: IR-receiver
static volatile uint32_t previousTicks = 0;
static volatile uint8_t pulseCount = 0;
static volatile uint32_t bitPattern = 0;

static volatile bool sleeping = false;


static void sleep() {
    // clear display
    tlcStop();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
}

_Noreturn static void reset()  {
    tlcStop();
    softwareReset = true;
    jumpToStart();
}


static void irCommands(uint32_t irCode) {
    switch (irCode) {
        case IR_OFF:
            sleeping = true;
            setLed(false);
            break;
        case IR_ON:
            reset();
        case IR_W:
            toggleLed();
            break;
        default:
            break;
    }

    if(sleeping) {
        sleep();
    }
}

/**
 * interprets ir input into code
 */
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
            pulseCount = 0;
            irCommands(bitPattern);
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
        reset();
    }
    int2FallingEdge = !int2FallingEdge;
}
