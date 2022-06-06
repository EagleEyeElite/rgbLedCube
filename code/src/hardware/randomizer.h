//
// Created by Conrad Klaus on 06.06.22.
//

#include "../config.h"

#ifndef RGBLEDCUBE_RANDOMIZER_H
#define RGBLEDCUBE_RANDOMIZER_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef EEPROM_WRITE
#define EEPROM_WRITE 0
#endif

#if EEPROM_WRITE
#define WRITE_EEPROM(VALUE) {eeprom_write_byte((uint8_t *) 4, VALUE);}
#else
#define WRITE_EEPROM(VALUE)
#endif


void initRandom();


#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_RANDOMIZER_H
