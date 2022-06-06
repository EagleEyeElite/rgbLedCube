/**
 * Timer1 generates a clock signal for the led driver.
 * The clock signal connects to GSCLK of the TLC5940.
 */

#ifndef RGBLEDCUBE_TIMER1_H
#define RGBLEDCUBE_TIMER1_H

#include <stdint.h>
#include <stdint-gcc.h>

#ifdef __cplusplus
extern "C" {
#endif

void startGSCLK();
void stopGSCLK();

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_TIMER1_H
