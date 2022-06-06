//
// Created by Conrad Klaus on 06.06.22.
//

#include "sleep.h"
#include "display.h"
#include "driver/led.h"
#include <stdbool.h>
#include <avr/sleep.h>


static bool sleepingSt = false;


void sleep() {
    setLed(false);
    sleepingSt = true;
    disableDisplay();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
}

bool sleeping() {
    return sleepingSt;
}
