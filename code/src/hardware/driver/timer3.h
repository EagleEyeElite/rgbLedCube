/**
 * Timer 3 measures the global time.
 */

#pragma once

#include <stdint.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C" {
#endif

// timer
void startGlobalTime();
void stopGlobalTime();
void resetGlobalTime();
uint32_t getGlobalTick();

#ifdef __cplusplus
}
#endif
