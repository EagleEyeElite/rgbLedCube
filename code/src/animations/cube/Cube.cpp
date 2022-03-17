//
// Created by conrad on 3/18/20.
//

#include "Cube.h"

#include "../resources/vector/Vec.h"

#include <math.h>
#include <stdlib.h>

// default constructor
Cube::Cube(Vec &supportA, float sizeA) {
    support = &supportA;
    size = sizeA;
    for (bool &i : direction) {
        i = false;
    }

    hue = (unsigned int) (rand() % 360);
} //Cube


// for just outline, and color changed outline etc.
void Cube::loadCube(Frame &cubeFrame) {
    cubeFrame.resetFrame();
    float koo[3];
    unsigned int sizeInt = (unsigned int) size + 1;

    Color b = Color();

    auto numLed = (unsigned int) round(pow(sizeInt, 3));
    for (unsigned int i = 0; i < numLed; i++) { // for all led in cube
        float light = 1;
        for (unsigned int n = 0; n < 3; n++) {  // for all 3 edges
            auto position = (unsigned int) (round((i / (unsigned int) round(pow(sizeInt, n))) % sizeInt));
            if (position >= sizeInt - 1) {
                float f3;
                light *= modff(size, &f3);  // if on edge
            }
            if (!direction[n])
                position *= -1;
            koo[n] = (float) position + support->Matrix[n];
        }
        b.loadHSV(hue, 255, (uint8_t) (light * 255));
        cubeFrame.addLight(koo, b.rgb);
    }
}
