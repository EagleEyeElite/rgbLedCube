/**
 * The Tlc5940 drives the display.
 * Its a constant current led driver.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Data to be pushed directly into the led driver (tlc5940) registers.
 * Includes data for one layer: 9 led.
 * One led has 3 channels (RGB).
 * One channel has a 12 bit resolution.
 * 9 * 3 * 12 = 324 bits (41 bytes).
 */
typedef uint8_t rawLayerData[41];

void initTlc5940();
void disableTlc5940();


#ifdef __cplusplus
}
#endif
