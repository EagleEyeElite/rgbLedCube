/*
 * timer.cpp
 *
 * Created: 30/09/2018 22:55:27
 *  Author: Conrad
 */

#include "hardware.h"
#include <avr/interrupt.h>
#include <avr/io.h>

static volatile uint32_t t3_soft;    //timer3 software

// normal counter operation, 1024 prescaler, 51,2µs / 0,051ms resolution (1 tick = 51,2µs / 0,051ms)
// overflows after ~3,3 seconds
void timerSetup() {
    t3_soft = 0;
    TCCR3B = 1u << (unsigned) CS32 | 1u << (unsigned) CS30;
    TIMSK3 |= 1u << (unsigned) TOIE3;
}

ISR(TIMER3_OVF_vect, ISR_BLOCK) {
    t3_soft += 0xFFFF;
}

uint32_t getTimerTick() {
    TIMSK3 &= ~(1u << (unsigned) TOIE3);    // disable interrupt
    uint32_t val = t3_soft + TCNT3;
    uint8_t tifr = TIFR3;
    TIMSK3 |= (1u << (unsigned) TOIE3);     // enable interrupt
    if (tifr & (1u << (unsigned) TOV3)) // test if overflow occurred and
        val += 0xFFFF;
    return val;
}

void resetTimer() {
    TCNT3 = 0;
    t3_soft = 0;
}
