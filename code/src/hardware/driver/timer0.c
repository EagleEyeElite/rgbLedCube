//
// Created by Conrad Klaus on 06.06.22.
//

#include "timer0.h"

#include "../pinLayout.h"
#include "layerMosfets.h"
#include "tlc5940.h"
#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint-gcc.h>


static uint8_t *currentLayer;
static const rawLayerData *rawDisplayData;


void startLayerSwitching(uint8_t *currentLayerPointer, uint8_t rawDisplayDataPointer[3][41]) {
    currentLayer = currentLayerPointer;
    rawDisplayData = rawDisplayDataPointer;

    // control MSPIM - timer 0 interrupts: CTC mode, timer 0 interrupt on OCR2A, 1024 prescaler
    // interrupt after 3.2768ms, 101.7 hz refresh rate
    TCCR0A |= 1 << WGM01;
    OCR0A = 64;     // prescaler*OCR0A /20MHZ -> interrupt timing
    TIMSK0 |= 1 << OCIE0A;
    TCCR0B |= 1 << CS00 | 1 << CS02;    // start timer
}

void stopLayerSwitching() {
    TCCR0B &= ~(1 << CS00 | 1 << CS02); // stops timer 0
    TIFR0 |= 1<<OCF0A;  // clear Timer0 Output Compare A Match Flag
}

/**
 * The interrupt handles the display layer switching.
 * Preloaded data of the current layer is latched into the Led Driver and
 * the current layer gets enabled.
 * It also triggers the loading of the led driver with next layer data.
 */
ISR(TIMER0_COMPA_vect, ISR_BLOCK) {    // controls MSPIM upload and cube image
    uint8_t layer = *currentLayer;
    TCNT0 = 0;    // resets Counter
    PIND = 1 << BLANK;    // high (inverted) - resets TLC counter (4096)
    PIND = 1 << XLAT;    // latches new Data
    PIND = 1 << XLAT;
    setMosfets(layer++);
    // blank goes low to start the next cycle, TLC will start to recount
    // make sure there is a 1µS delay before switching it again! (PCB board inverter)
    PIND = 1 << BLANK; // low (inverted)

    if (layer >= 3) {
        layer = 0;
    }
    startTransmission(rawDisplayData[layer][0]);
    *currentLayer = layer;
}