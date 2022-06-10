//
// Created by Conrad Klaus on 06.06.22.
//

#include "randomizer.h"
#include "driver/reset.h"

#include <stdint.h>
#include <stdlib.h>
#include <avr/eeprom.h>


static uint8_t __attribute__((section (".noinit"))) seed_ram;


void initRandom() {
    // random setup
    uint8_t seed_eeprom = eeprom_read_byte((uint8_t *) 4) + 1;
    if(resetBySoftware()) {
        seed_ram++;
    } else {
        seed_ram = 0;
        WRITE_EEPROM(seed_eeprom)
    }
    uint16_t seed = (seed_ram << 8) + seed_eeprom;
    srand(seed);
}
