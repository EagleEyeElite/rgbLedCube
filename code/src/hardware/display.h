//
// Created by Conrad Klaus on 06.06.22.
//

#ifndef RGBLEDCUBE_DISPLAY_H
#define RGBLEDCUBE_DISPLAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define L(VALUE) (lightness[image[VALUE]])

void startDisplay();
void disableDisplay();
void updateDisplay(const uint8_t image[81]);

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_DISPLAY_H
