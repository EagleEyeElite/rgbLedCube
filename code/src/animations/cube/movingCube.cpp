//
// Created by conrad on 3/18/20.
//


#include "../resources/vector/Vec.h"
#include "Cube.h"

#include <avr/io.h>
#include <stdlib.h>    //rand

static void
playAnimationsA(void (*f)(float, Frame *, Cube *, Vec *, const unsigned int *), Clock *Watch, Frame *panelFrame,
                Cube *CubeA, Vec *supportA, unsigned int *startPos);

static void bloatCube(float progress, Frame *panelFrame, Cube *CubeA, Vec *supportA, const unsigned int *startPos);

static void popCube(float progress, Frame *panelFrame, Cube *CubeA, Vec *supportA, const unsigned int *startPos);

void createCube() {
    Clock Watch(500);
    Frame panelFrame(false);

    Vec supportA(0, 0, 0);
    Cube CubeA(supportA, 3);

    unsigned int startPos[3];
    unsigned int endPos[3] = {1, 1, 1};

    for (unsigned int &startPo : startPos)
        startPo = (unsigned int) (rand() % 2) * 2 + 1;

    for (unsigned int n = 0; n < 40; n++) {  // iterations
        for (unsigned int &endPo : endPos)
            endPo = (unsigned int) (rand() % 2) * 2 + 1;
        playAnimationsA(bloatCube, &Watch, &panelFrame, &CubeA, &supportA, startPos);

        for (unsigned int &startPo : startPos)
            startPo = (unsigned int) (rand() % 2) * 2 + 1;
        playAnimationsA(popCube, &Watch, &panelFrame, &CubeA, &supportA, startPos);
    }
}


static void
playAnimationsA(void (*f)(float, Frame *, Cube *, Vec *, const unsigned int *), Clock *Watch, Frame *panelFrame,
                Cube *CubeA, Vec *supportA, unsigned int *startPos) {
    while ((*Watch).getProgress() <= 1) {
        (*panelFrame).resetFrame();
        f((*Watch).getProgress(), panelFrame, CubeA, supportA, startPos);
        (*panelFrame).showFrame();
    }
    (*Watch).resetTimer();
}

static void bloatCube(float progress, Frame *panelFrame, Cube *CubeA, Vec *supportA, const unsigned int *startPos) {
    for (uint8_t i = 0; i <= 2; i++) {
        (*CubeA).direction[i] = true;
        if (startPos[i] == 3)
            (*CubeA).direction[i] = false;
        (*supportA).Matrix[i] = (float) startPos[i];
    }
    (*CubeA).size = (progress * 4);
    (*CubeA).loadCube(*panelFrame);
}

static void popCube(float progress, Frame *panelFrame, Cube *CubeA, Vec *supportA, const unsigned int *startPos) {
    for (uint8_t i = 0; i <= 2; i++) {
        (*CubeA).direction[i] = true;
        if (startPos[i] == 3)
            (*CubeA).direction[i] = false;
        (*supportA).Matrix[i] = (float) startPos[i];
    }
    (*CubeA).size = (1 - progress) * 4;
    (*CubeA).loadCube(*panelFrame);
}
