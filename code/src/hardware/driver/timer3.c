/*
 * timer.cpp
 *
 * Created: 30/09/2018 22:55:27
 *  Author: Conrad
 */

#include "timer3.h"

#include <avr/interrupt.h>
#include <avr/io.h>

static uint32_t t3_soft;    //timer3 software

/**
 * Initialize timer for global clock.
 */
void startGlobalTime() {
    // normal counter operation, 1024 prescaler, 51,2µs / 0,051ms resolution (1 tick = 51,2µs / 0,051ms)
    // overflows after ~3,3 seconds
    t3_soft = 0;
    TCCR3B = 1 << CS32 | 1 << CS30;
    TIMSK3 |= 1 << TOIE3;
}

void stopGlobalTime() {
    TIMSK3 &= ~(1 << TOIE3);    // disable interrupt
    TCCR3B &= ~(1 << CS32 | 1 << CS30); // stop clock
    t3_soft = 0;
}

/**
 * On Timer overflow, update the timer3 software timer to keep track of time.
 */
ISR(TIMER3_OVF_vect, ISR_BLOCK) {
    t3_soft += 0xFFFF;
}

/**
 * @return global time ticks since reset.
 */
uint32_t getGlobalTick() {
    TIMSK3 &= ~(1 << TOIE3);    // disable interrupt
    uint32_t val = t3_soft + TCNT3;
    uint8_t tifr = TIFR3;
    TIMSK3 |= 1 << TOIE3;     // enable interrupt
    if (tifr & (1 << TOV3)) // test if overflow occurred and
        val += 0xFFFF;
    return val;
}

void resetGlobalTime() {
    TCNT3 = 0;
    t3_soft = 0;
}
