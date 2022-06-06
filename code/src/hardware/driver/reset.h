#ifndef RGBLEDCUBE_RESET_H
#define RGBLEDCUBE_RESET_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


void initResetState();
bool resetBySoftware();
_Noreturn void reset();

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_RESET_H
