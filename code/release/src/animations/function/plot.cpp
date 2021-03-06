//
// Created by conrad on 3/19/20.
//

#include <stdlib.h>
#include "plot.h"
#include "../resources/vector/vect.h"

// default constructor
plot::plot(vect &coordinateOriginal, float (*fa)(float), float (*fb)(float), float (*fc)(float)) {
    f[0] = fa;
    f[1] = fb;
    f[2] = fc;

    Axis[0] = 0;
    Axis[1] = 1;
    Axis[2] = 2;

    coordinate_origin = &coordinateOriginal;

    colours = (colour *) malloc(sizeof(colour));
    *colours = colour();
    (*colours).loadHSV((unsigned int) rand() % 360, 255, 255);
}

plot::~plot() {
    free(colours);
}

void plot::setAxis(uint8_t x, uint8_t y, uint8_t z) {
    Axis[0] = x;
    Axis[1] = z;
    Axis[2] = y;
}

void plot::loadPoint(frame &FrameA, float x) {
    FrameA.resetFrame();

    float Koo[3];
    for (uint8_t i = 0; i <= 2; i++) {
        Koo[i] = f[Axis[i]](x) + coordinate_origin->Matrix[Axis[i]];
        if (0 > Koo[i] || Koo[i] > 4)
            return;
    }
    FrameA.addLight(Koo, (*colours).rgb);
}
