/**
 * The Tlc5940 drives the display.
 * Its a constant current led driver.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t rawLayerData[41];

void initTlc5940();
void disableTlc5940();


#ifdef __cplusplus
}
#endif
