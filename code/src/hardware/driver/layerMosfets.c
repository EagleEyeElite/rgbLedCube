//
// Created by Conrad Klaus on 06.06.22.
//

#include "layerMosfets.h"
#include <avr/io.h>

void initDisplayLayerMosfets() {
    // PC0-PC2 mosfet-Outputs (inverted)
    PORTC = 0b00000111;    // disable mosfet output (pins are inverted on pcb)
    DDRC = 0b00000111;    // mosfet - output
}

inline void setMosfets(uint8_t layer) {
    PORTC = (uint8_t) (~(0b001u << layer));
}

void disableDisplayLayerMosfets() {
    PORTC = 0b00000111;
}
