/*
 * straight.cpp
 *
 * Created: 18/01/2019 00:24:30
 *  Author: Conrad
 */

#include <stdlib.h>
#include "straight.h"

#include "vect.h"
#include "../../../interface/interface.h"

straight::straight(vect &supportX, vect &directionA) {
    support = &supportX;
    direction = &directionA;

    colours = (colour *) malloc(sizeof(colour));
    *colours = colour();
    (*colours).loadHSV((unsigned int) rand() % 360, 255, 255);
}

straight::~straight() {
    free(colours);
}

void straight::loadStraight(frame &straightFrame) {
    straightFrame.resetFrame();

    float supportTemp[3];
    for (unsigned int i = 0; i < 3; i++)
        supportTemp[i] = support->Matrix[i];
    moveSupport(supportTemp, direction->Matrix);

    int8_t limit[2];
    calcLimit(limit, supportTemp, direction->Matrix);

    float Koo[3];
    for (int8_t a = limit[0]; a <= limit[1]; a++) {
        for (unsigned int i = 0; i < 3; i++)
            Koo[i] = supportTemp[i] + (direction->Matrix[i] * ((float) a));
        straightFrame.addLight(Koo, (*colours).rgb);
    }
}

//straight
