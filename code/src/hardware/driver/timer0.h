/**
 * Timer0 updates the display.
 * The 3D Display can only display a layer at a time.
 * Timer0 generates precise interrupts to switch between layers.
 */


#pragma once

#include "tlc5940.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdint-gcc.h>

#ifdef __cplusplus
extern "C" {
#endif

void startLayerSwitching(uint8_t *currentLayerPointer, uint8_t rawDisplayDataPointer[3][41]);
void stopLayerSwitching();

#ifdef __cplusplus
}
#endif
