//
// Created by Conrad Klaus on 06.06.22.
//

#include "reset.h"

#include "../display.h"

#include <stdbool.h>
#include <avr/wdt.h>


static bool softwareReset __attribute__((section (".noinit")));
static bool resetBySoftwareState = false;

static void disableWatchdog() {
    wdt_reset();
    //Clear WDRF in MCUSR
    MCUSR &= ~(1<<WDRF);
    //Write logical one to WDCE and WDE
    // Keep old prescaler setting to prevent unintentional time-out
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR = 0x00;  // Turn off WDT
}

void initResetState() {
    disableWatchdog();
    resetBySoftwareState = softwareReset;
    softwareReset = false;
}

bool resetBySoftware() {
    return resetBySoftwareState;
}

_Noreturn void reset()  {
    disableDisplay();
    softwareReset = true;
    wdt_enable(WDTO_15MS);
    while(true);
}
