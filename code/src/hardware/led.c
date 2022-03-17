//
// Created by ckl on 17/03/2022.
//

#include "led.h"
#include <avr/io.h>

#include <stdbool.h>

void initLed() {
    DDRD |= 1u << (unsigned) LED;
    setLed(false);
}
void setLed(bool on) {
    if (on)
        PORTD |= 1 << LED;
    else
        PORTD &= ~(1<<LED);
}

void toggleLed() {
    PIND |= 1u << (unsigned) LED;    // toggle Status LED
}
