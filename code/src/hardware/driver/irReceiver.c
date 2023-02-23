//
// Created by Conrad Klaus on 06.06.22.
//

#include "irReceiver.h"

#include "../irCodes.h"
#include "led.h"
#include "reset.h"
#include "timer3.h"
#include "../display.h"
#include "../sleep.h"

#include <avr/io.h>
#include <avr/sleep.h>

void initIR() {
    // IR receiver - INT0 falling edge interrupt
    EICRA |= 1 << ISC01;    // configure INT0 falling edge interrupt
    EIMSK |= 1 << INT0;        // enable the INT0 external interrupt
}

static void irCommands(uint32_t irCode) {
    switch (irCode) {
        case IR_OFF:
            sleep();
            break;
        case IR_ON:
            reset();
        case IR_W:
            toggleLed();
            break;
        default:
            break;
    }

    if(sleeping()) {
        sleep();
    }
}


static uint32_t previousTicks = 0;
static uint8_t pulseCount = 0;
static uint32_t bitPattern = 0;
static bool newKey = false;
static bool recordingFrame = false;

/**
 * interprets ir input into code and executes the command.
 */
ISR(INT0_vect, ISR_NOBLOCK) {
    uint32_t tempTicks = getGlobalTick();    // 1 tick = 0.0512ms
    uint32_t counterTicks = tempTicks - previousTicks;
    previousTicks = tempTicks;
    if (counterTicks >= 500) {    // start of frame (25ms)
        bitPattern = 0;
        pulseCount = 0;
        newKey = true;
        recordingFrame = false;
        return;
    }
    if (newKey) {
        newKey = false;
        // indicates start of frame
        // time should be between 11.5 ms and 15.3 ms (ideal: 13.5ms)
        if (counterTicks >= 224 && counterTicks <= 298) {
            recordingFrame = true;
        }
        return;
    }
    if (recordingFrame) {
        bitPattern <<= 1;
        if (counterTicks > 31) {    // logical one are longer than 33 ticksUntilReactivated
            bitPattern |= 1;
        }
        if (pulseCount++ > 30) {    // marks end of message
            recordingFrame = false;
            irCommands(bitPattern);
        }
        return;
    }
}
