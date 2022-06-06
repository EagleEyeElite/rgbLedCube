/* 
* Clock.cpp
*
* Created: 30/09/2018 23:33:17
* Author: Conrad
*/

#include "Clock.h"

#include "../hardware/hardware.h"
#include "../hardware/driver/led.h"
#include "../hardware/driver/timer3.h"
#include <avr/io.h>
#include <avr/eeprom.h>

// default constructor
Clock::Clock(uint16_t maxMillis) {
    counterStart = getGlobalTick();
    maxTicks = static_cast<uint32_t>(maxMillis * 19.532125);
}

float Clock::getProgress() {
    return static_cast<float>(getGlobalTick() - counterStart) / maxTicks;
}

void Clock::resetTimer() {
    counterStart = getGlobalTick();
} //Clock

void delay(uint16_t time) {
    uint32_t counterStart = getGlobalTick();
    auto tick = static_cast<uint32_t>(time * 19.532125);
    while (getGlobalTick() - counterStart <= tick) {}
}

void benchmark(void (*f)(), uint16_t run_cycles) {
    setLed(false);
    uint32_t counterStart = getGlobalTick();

    for (uint16_t i = 0; i < run_cycles; i++) {    //take average for better results
        f();
    }
    uint32_t ticks_needed = getGlobalTick() - counterStart;
    eeprom_update_dword((uint32_t *) nullptr, ticks_needed);

    setLed(true);   //led -high, Indicates end of benchmark
}
