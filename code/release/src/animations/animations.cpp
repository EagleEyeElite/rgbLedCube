/*
 * animations.cpp
 *
 * Created: 07/05/2019 17:51:23
 *  Author: Conrad
 */

#include <stdlib.h>
#include "animations.h"
#include "cube/cube.h"
#include "function/Graph.h"
#include "function/Plot.h"

void runAnimations() {
    void (*p[11])() = {rotatingSinWave, snake, vulcan, createCube, jumpingWave, rain, rotatingStraight, panelAnimation,
                       randomVocals, infinityFigure, circleFigure};

    while (true) {
        p[rand() % 10]();
    }
}

void basic() {
    glowingCube();
    runningLed();
    defaultImages();
    fadingLed();
    flashingCube();
    stackingLayer();
    redCube();
    fadeInFadeOut();
    fadePreset();
}
