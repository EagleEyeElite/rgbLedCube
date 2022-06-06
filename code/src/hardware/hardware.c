/*
 * hardware.c
 *
 * Created: 02/10/2018 16:37:18
 *  Author: Conrad
 */


#include "hardware.h"

#include "driver/led.h"
#include "driver/reset.h"
#include "driver/irReceiver.h"
#include "randomizer.h"
#include "driver/button.h"
#include "driver/timer3.h"
#include "display.h"


/**
 * Start and initialize Hardware.
 */
void initHardware() {
    cli();
    initLed();
    initResetState();
    initRandom();
    initButton();
    startGlobalTime();
    initIR();
    startDisplay();
    sei();    // enable interrupt globally
}
