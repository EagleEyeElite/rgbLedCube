//
// Created by Conrad Klaus on 06.06.22.
//

#include "tlc5940.h"
#include "../pinLayout.h"
#include <avr/io.h>


void pulse(uint8_t pin) {
    PORTD |= 1 << pin;
    PORTD &= ~(1 << pin);
}

/**
 * Flushes all old data in TLC5940 and enable TLC output.
 * All pins cannot be overwritten by any peripherals.
 */
void initTlc5940() {
    disableTlc5940();
    DDRD |= 1 << BLANK | 1 << VPRG | 1 << SIN | 1 << SCLK | 1 << GSCLK | 1 << XLAT;    // define as output

    PORTD |= 1 << VPRG; // Dot Correction (DC) data input mode
    PORTD |= 1 << SIN;  // all channels should operate at 100%.
    for (unsigned int i = 0; i < 162; i++) {     // 6 bits * 27 channels = 162
        pulse(SCLK);
    }
    pulse(XLAT);    // latch DC data

    PORTD &= ~(1 << VPRG);  // Grayscale (GS) data input mode
    PORTD &= ~(1 << SIN);   // clear all old data
    for (unsigned int i = 0; i < 324; i++) {     // 12bits * 27 channels = 324
        pulse(SCLK);
    }
    pulse(XLAT); // latch GS data

    PORTD |= (1 << BLANK);  // enable TLC output (the signal gets inverted on the pcb, and is low on the chip)
}

void disableTlc5940() {
    // turn off whole tlc, blank is via the pcb inverted, and high on the chip
    PORTD &= ~(1 << BLANK | 1 << VPRG | 1 << SIN | 1 << SCLK | 1 << GSCLK | 1 << XLAT);
}
