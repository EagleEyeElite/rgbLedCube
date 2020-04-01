/*
 * animations.cpp
 *
 * Created: 07/05/2019 17:51:23
 *  Author: Conrad
 */

#include <stdlib.h>
#include "animations.h"
#include "cube/cube.h"
#include "function/graph.h"
#include "function/plot.h"

void runAnimations() {
    void (*p[11])() = {rotatingSinWave, snake, vulcan, createCube, jumpingWave, rain, rotatingStraight, panelAnimation,
                       randomVocals, infinityFigure, circleFigure};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {

        p[rand() % 10]();
    }
#pragma clang diagnostic pop
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
