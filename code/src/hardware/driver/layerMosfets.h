/**
 * The mosfets enable and disable the layers of the led cube.
 */

#ifndef RGBLEDCUBE_LAYERMOSFETS_H
#define RGBLEDCUBE_LAYERMOSFETS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void initDisplayLayerMosfets();
void setMosfets(uint8_t layer);
void disableDisplayLayerMosfets();

#ifdef __cplusplus
}
#endif
#endif //RGBLEDCUBE_LAYERMOSFETS_H
