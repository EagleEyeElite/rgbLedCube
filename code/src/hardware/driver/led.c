//
// Created by ckl on 17/03/2022.
//

#include "led.h"
#include "../pinLayout.h"
#include <avr/io.h>

#include <stdbool.h>

/**
 * initialize debug led on pcb.
 */
void initLed() {
    DDRD |= 1 << LED;
    setLed(false);
}
void setLed(bool on) {
    if (on)
        PORTD |= 1 << LED;
    else
        PORTD &= ~(1<<LED);
}

void toggleLed() {
    PIND |= 1 << LED;    // toggle Status LED
}
