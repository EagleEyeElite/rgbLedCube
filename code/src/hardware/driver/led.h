#ifndef RGBLEDCUBE_LED_H
#define RGBLEDCUBE_LED_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


void initLed();
void setLed(bool on);
void toggleLed();

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_LED_H
