/**
 * The USART is used in Master SPI Mode (MSPIM).
 * It loads the display data into the Led Driver.
 */

#ifndef RGBLEDCUBE_USART_H
#define RGBLEDCUBE_USART_H

#include "tlc5940.h"
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void initDisplayDataTransmitter(const uint8_t *currentLayerPointer, unsigned char rawDisplayDataPointer[3][41]);
void disableDisplayDataTransmitter();
void startTransmission(uint8_t data);

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_USART_H
