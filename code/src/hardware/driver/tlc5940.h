/**
 * The Tlc5940 drives the display.
 * Its a constant current led driver.
 */

#ifndef RGBLEDCUBE_TLC5940_H
#define RGBLEDCUBE_TLC5940_H

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
#endif //RGBLEDCUBE_TLC5940_H
