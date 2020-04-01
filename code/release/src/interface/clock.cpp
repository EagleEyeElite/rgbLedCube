/* 
* clock.cpp
*
* Created: 30/09/2018 23:33:17
* Author: Conrad
*/

#include "clock.h"

#include "../hardware/hardware.h"
#include <avr/io.h>
#include <avr/eeprom.h>

// default constructor
clock::clock(uint16_t maxMillis) {
    counterStart = getTimerTick();
    maxTicks = static_cast<uint32_t>(maxMillis * 19.532125);
}

float clock::getProgress() {
    return static_cast<float>(getTimerTick() - counterStart) / maxTicks;
}

void clock::resetTimer() {
    counterStart = getTimerTick();
} //clock

void delay(uint16_t time) {
    uint32_t counterStart = getTimerTick();
    auto tick = static_cast<uint32_t>(time * 19.532125);
    while (getTimerTick() - counterStart <= tick) {}
}

void benchmark(void (*f)(), uint16_t run_cycles) {
    PORTD &= ~(1u << (unsigned) LED);    //led -low
    uint32_t counterStart = getTimerTick();

    for (uint16_t i = 0; i < run_cycles; i++) {    //take average for better results
        f();
    }
    uint32_t ticks_needed = getTimerTick() - counterStart;
    eeprom_update_dword((uint32_t *) nullptr, ticks_needed);

    PORTD |= (1u << (unsigned) LED);    //led -high, Indicates end of benchmark
}
