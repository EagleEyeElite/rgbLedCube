//
// Created by Conrad Klaus on 06.06.22.
//

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void setSleepingState(bool sleeping);
bool sleeping();
void sleep();


#ifdef __cplusplus
}
#endif
