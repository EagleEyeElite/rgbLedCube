//
// Created by Conrad Klaus on 06.06.22.
//

#include "button.h"

#include "reset.h"
#include "../pinLayout.h"
#include "timer3.h"
#include "../sleep.h"

#include <avr/io.h>
#include <stdbool.h>

void initButton() {
    // switch1 - tristate (Hi-Z), external interrupt on any edge
    DDRB |= 0 << SW;
    PORTB |= 1 << SW;
    EICRA |= 1 << ISC20;
    EIMSK |= 1 << INT2;
}


static uint32_t int2Ticks = 0;
static bool buttonPressed = false;
/**
 * handles button presses
 */
ISR(INT2_vect, ISR_NOBLOCK) {
    uint32_t tempTicks = getGlobalTick();    // 1 tick = 0.0512ms
    if (tempTicks <= int2Ticks) {   // check for debounce
        return;
    }
    int2Ticks = tempTicks + 500;  // 25.5 ms - max debounce time
    buttonPressed = !buttonPressed;
    if (!buttonPressed) {
        return;
    }

    // code to be executed
    if (sleeping()) {
        reset();
    } else {
        sleep();
    }
}
