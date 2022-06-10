//
// Created by Conrad Klaus on 06.06.22.
//

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define L(VALUE) (lightness[image[VALUE]])

/**
 * 3 channels (RGB) per led.
 * One channel has a 8 bit resolution.
 * 27 led * 3 channels => 81
 */
typedef uint8_t imageData[81];

void startDisplay();
void disableDisplay();
void updateDisplay(const imageData image);

#ifdef __cplusplus
}
#endif
