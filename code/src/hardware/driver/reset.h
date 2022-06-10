#pragma once

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
