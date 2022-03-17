//
// Created by conrad on 3/19/20.
//

#include "Graph.h"
#include <avr/io.h>
#include <stdlib.h>

// default constructor
Graph::Graph(Vec &coordinateOriginal, float (*f)(int8_t, int8_t, float)) {
    fx = f;

    Axis[0] = 0;
    Axis[1] = 1;
    Axis[2] = 2;

    scale[0] = 1;
    scale[1] = 1;

    coordinate_origin = &coordinateOriginal;

    colours = (Color *) malloc(sizeof(Color));
    *colours = Color();
    (*colours).loadHSV((unsigned int) (rand() % 360), 255, 255);

} //ThreeDGraph

Graph::~Graph() {
    free(colours);
}

void Graph::setAxis(uint8_t x, uint8_t y, uint8_t z) {
    Axis[0] = x;
    Axis[1] = z;
    Axis[2] = y;
}

void Graph::loadGraph(Frame &FrameA, float progress) {
    FrameA.resetFrame();
    for (unsigned int x = 1; x < 4; x++) {
        for (unsigned int y = 1; y < 4; y++) {
            float Koo[] = {(float) x, (float) y, fx(
                    static_cast<int8_t>(((float) x - (coordinate_origin->Matrix[Axis[0]])) * scale[0]),
                    static_cast<int8_t>(((float) y - (coordinate_origin->Matrix[Axis[1]])) * scale[1]),
                    progress) + (coordinate_origin->Matrix[Axis[2]])};

            float translatedPoint[3];
            for (unsigned int i = 0; i < 3; i++) {
                translatedPoint[i] = Koo[Axis[i]];
            }
            if (0 < translatedPoint[1] && translatedPoint[1] < 4)
                FrameA.addLight(translatedPoint, (*colours).rgb);
        }
    }
} //Function
