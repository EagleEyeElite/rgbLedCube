#ifndef RGBLEDCUBE_LED_H
#define RGBLEDCUBE_LED_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


#define LED 7   //PD7

void initLed();
void setLed(bool on);
void toggleLed();

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_LED_H
