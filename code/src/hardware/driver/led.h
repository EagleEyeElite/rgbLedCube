#pragma once

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
