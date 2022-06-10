/**
 * The USART is used in Master SPI Mode (MSPIM).
 * It loads the display data into the Led Driver.
 */

#pragma once

#include "tlc5940.h"
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void initDisplayDataTransmitter(rawLayerData rawDisplayDataPointer[3]);
void disableDisplayDataTransmitter();
void startTransmission(uint8_t layer);

#ifdef __cplusplus
}
#endif
