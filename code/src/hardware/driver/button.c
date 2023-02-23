//
// Created by Conrad Klaus on 06.06.22.
//

#include "button.h"

#include "reset.h"
#include "../pinLayout.h"
#include "timer3.h"
#include "../sleep.h"
#include "led.h"

#include <avr/io.h>
#include <stdbool.h>

static void onButtonPressed();

void initButton() {
    // switch1 - tristate (Hi-Z), external interrupt on any edge
    DDRB |= 0 << SW;
    PORTB |= 1 << SW;
    EICRA |= 1 << ISC20;
    EIMSK |= 1 << INT2;
}

/// time until button no longer bounces
static uint32_t ticksUntilReactivated = 0;
static bool isPressedSoftware = false;  // TODO add software check, debounce doesent always work

/**
 * handles button presses
 */
ISR(INT2_vect, ISR_NOBLOCK) {
    uint32_t ticks = getGlobalTick();
    if (ticks < ticksUntilReactivated) {
        return;
    }
    // TODO whats the best value for this?
    // 2000 ticks = 102.4ms
    // 500 ticks = 25.6ms
    ticksUntilReactivated = ticks + 3000;
    bool risingEdge = PINB & (1 << SW);
    bool isPressed = !risingEdge;
    if (!isPressed) {
        return;
    }
    //toggleLed();
    onButtonPressed();
}

enum StatesButton { isSleeping, isRunning };
static enum StatesButton currentState = isRunning;

static void onButtonPressed() {
    switch (currentState) {
        case isSleeping:
            currentState = isRunning;
            reset();
        case isRunning:
            currentState = isSleeping;
            sleep();
    }
}
