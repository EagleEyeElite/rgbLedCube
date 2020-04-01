//
// Created by conrad on 3/19/20.
//

#include "graph.h"
#include "../resources/vector/vect.h"
#include "plot.h"
#include <math.h>

static float ix(float x) {
    return (float) cos(x);
}

static float iy(float x) {
    return (float) sin(2 * x);
}

static float iz(float x __attribute__((unused))) {
    return 0;
}

void infinityFigure() {
    clock Watch(1000);
    frame FrameA(true);
    vect support(2, 2, 2);
    plot plot(support, ix, iy, iz);

    while (Watch.getProgress() <= 10) {
        plot.loadPoint(FrameA, Watch.getProgress() * 2 * (float) M_PI);
        FrameA.showFrame();
    }
}

static float cx(float x) {
    return (float) cos(x);
}

static float cy(float x) {
    return (float) sin(x);
}

static float cz(float x) {
    return (float) cos(x);
}

void circleFigure() {
    clock Watch(1000);
    frame FrameA(true);
    vect support(2, 2, 2);
    plot plot(support, cx, cy, cz);

    while (Watch.getProgress() <= 10) {
        plot.loadPoint(FrameA, Watch.getProgress() * 2 * (float) M_PI);
        FrameA.showFrame();
    }
}
