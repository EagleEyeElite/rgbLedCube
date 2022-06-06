//
// Created by Conrad Klaus on 06.06.22.
//

#ifndef RGBLEDCUBE_SLEEP_H
#define RGBLEDCUBE_SLEEP_H

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

#endif //RGBLEDCUBE_SLEEP_H
