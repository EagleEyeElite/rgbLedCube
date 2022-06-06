//
// Created by Conrad Klaus on 06.06.22.
//

#ifndef RGBLEDCUBE_PINLAYOUT_H
#define RGBLEDCUBE_PINLAYOUT_H


#define SW 2    // PB2 - switch

#define Layer0 0    // PC0 - mosfet for led layer
#define Layer1 1    // PC1
#define Layer2 2    // PC2

#define BLANK 0 // PD0 - when low, it's high on the pcb and disables the tlc output
#define VPRG 1  // PD1 - sets grayscale / dot correction (dc) mode
#define IR_Rec 2    // PD2
#define SIN 3   // PD3 - serial in
#define SCLK 4  // PD4 - serial clock
#define GSCLK 5 // PD5	//OC1A - grayscale clock
#define XLAT 6  // PD6 - latches serial data into registers
#define LED 7   // PD7

#endif //RGBLEDCUBE_PINLAYOUT_H
