//
// Created by Conrad Klaus on 06.06.22.
//

#include "usart.h"
#include "../pinLayout.h"
#include "tlc5940.h"

#include <avr/io.h>

static const rawLayerData *rawDisplayData;

/**
 * Overrides serial clock (SCLK) snd Serial in (Sin) pins.
 * Initialize USART for data transfer.
 *
 * @param rawDisplayDataPointer
 */
void initDisplayDataTransmitter(rawLayerData rawDisplayDataPointer[3]) {
    rawDisplayData = rawDisplayDataPointer;

    // Master SPI Mode (MSPIM): starts USART as SPI: SPI-mode 0, MSB, baud rate: 0
    // transmitter enable, USART data register empty interrupt enable
    UBRR1 = 0;
    DDRD |= 1 << SCLK;
    UCSR1C = 1 << UMSEL10 | 1 << UMSEL11;
    UCSR1B |= 1 << TXEN1 | 1 << UDRIE1;
    UBRR1 = 0; // highest baud rate available
}

/**
 * Disable USART and release SCLK and SIN pins.
 */
void disableDisplayDataTransmitter() {
    // if usart as spi transmitter enabled
    if (UCSR1B & (1<<TXEN1)) {
        UCSR1B = 0; // disable usart transmitter port overwrite and interrupts
        UCSR1C = 0; // disable MSPI mode
        while (!(UCSR1A & (1 << TXC1))); // wait until current transmission is complete
    }
}

static inline void writeTransmitBuffer(uint8_t data) {
    UCSR1A |= 1 << TXC1; // clear USART Transmit Complete
    UDR1 = data;    // upload shiftOutBuffer[]
}

static uint8_t currentLayer;
static uint8_t byteNr;

/**
 * Start the transmission of a new layer package for the led Driver.
 * @param data first byte of layer package
 */
inline void startTransmission(uint8_t layer) {
    writeTransmitBuffer(rawDisplayData[layer][0]);
    currentLayer = layer;
    byteNr = 1;
    UCSR1B |= 1 << UDRIE1; // enable emtpy transmit buffer interrupt
}

/**
 * The interrupt fills the USART Buffer until the whole layer package is written to the LED Driver.
 */
ISR(USART1_UDRE_vect, ISR_BLOCK) {    // clocks in data
    writeTransmitBuffer(rawDisplayData[currentLayer][byteNr++]);
    if (byteNr > 40) { // sendLength = 41, (27*12 bits -> 40.5 * 8bits)
        // this is the last data needed
        UCSR1B &= ~(1 << UDRIE1); // disable further empty buffer interrupts
    }
}
