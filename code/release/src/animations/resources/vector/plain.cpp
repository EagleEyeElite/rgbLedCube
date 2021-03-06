/*
 * plain.cpp
 *
 * Created: 18/01/2019 00:24:17
 *  Author: Conrad
 */

#include "plain.h"

#include "vect.h"
#include "../../../interface/interface.h"

plain::plain(vect &supportX, vect &directionX, vect &directionBX) {
    support = &supportX;
    direction[0] = &directionX;
    direction[1] = &directionBX;
}

void plain::loadPlain(frame &plainFrame, uint8_t brightness) {
    plainFrame.resetFrame();
    float supportTemp[3];

    calcPlainPos(supportTemp, support->Matrix, direction[0]->Matrix, direction[1]->Matrix);

    moveSupport(supportTemp, direction[0]->Matrix);

    int8_t limitA[2];
    calcLimit(limitA, supportTemp, direction[0]->Matrix);
    int8_t limitB[2];
    calcLimit(limitB, supportTemp, direction[1]->Matrix);
    colour B = colour(brightness, brightness, brightness);

    float Koo[3];
    for (int a = limitA[0] - 1; a <= limitA[1] + 1; a++) {
        for (int b = limitB[0] - 1; b <= limitB[1] + 1; b++) {
            for (unsigned int i = 0; i < 3; i++)
                Koo[i] = supportTemp[i] + direction[0]->Matrix[i] * (float) a + direction[1]->Matrix[i] * (float) b;
            plainFrame.addLight(Koo, B.rgb);
        }
    }
}

//plain
