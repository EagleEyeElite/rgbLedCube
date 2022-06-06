/**
 * Timer 3 measures the global time.
 */

#ifndef RGBLEDCUBE_TIMER3_H
#define RGBLEDCUBE_TIMER3_H

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
#endif //RGBLEDCUBE_TIMER3_H
