//
// Created by conrad on 3/19/20.
//

#include "graph.h"
#include "../resources/vector/vect.h"
#include <math.h>

static float sinWaveFunction(int8_t x, int8_t y, float progress) {
    return (float) sin((progress * 2 * (float) M_PI * 24) + x * cos(progress * 2 * (float) M_PI) +
                       y * sin(progress * 2 * (float) M_PI));
}

void rotatingSinWave() {
    clock Watch(20000);
    frame FrameA(true);

    vect support(1, 1, 2);
    graph Wave(support, sinWaveFunction);

    Wave.scale[0] = (2 * (float) M_PI) / 5;
    Wave.scale[1] = (2 * (float) M_PI) / 5;

    while (Watch.getProgress() <= 3) {

        Wave.loadGraph(FrameA, Watch.getProgress());
        FrameA.showFrame();
    }
}

static float vulcanFunction(int8_t x, int8_t y, float progress) {
    return (progress * 4) / (float) (x * x + y * y);
}

void vulcan() {
    clock Watch(5000);
    frame FrameA(true);

    vect support(2, 2, 1);
    graph Graph(support, vulcanFunction);

    while (Watch.getProgress() <= 1) {
        Graph.loadGraph(FrameA, Watch.getProgress());
        FrameA.showFrame();
    }
}

static float jumpingWaveFunction(int8_t x, int8_t y, float progress) {
    return (float) cos((2 * (float) M_PI * progress) + 2 * sqrt(x * x + y * y));
}

void jumpingWave() {
    clock Watch(1000);
    frame FrameA(true);

    vect support(2, 2, 2);
    graph Graph(support, jumpingWaveFunction);


    Graph.scale[0] = (2 * (float) M_PI) / 5;
    Graph.scale[1] = (2 * (float) M_PI) / 5;

    while (Watch.getProgress() <= 10) {
        Graph.loadGraph(FrameA, Watch.getProgress());
        FrameA.showFrame();
    }
}
