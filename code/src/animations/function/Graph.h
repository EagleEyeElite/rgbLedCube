//
// Created by conrad on 3/19/20.
//

#include "../resources/vector/Vec.h"
#include "../../interface/interface.h"
#include <avr/io.h>

#ifndef RGBLEDCUBE_GRAPH_H
#define RGBLEDCUBE_GRAPH_H

void rotatingSinWave();

void vulcan();

void jumpingWave();

class Graph {
public:
    Graph(Vec &coordinateOriginal, float (*f)(int8_t x, int8_t y, float progress));

    ~Graph();

    void setAxis(uint8_t x, uint8_t y, uint8_t z);  // may be used to switch axis

    void loadGraph(Frame &graphFrame, float progress);

    Vec *coordinate_origin;
    float scale[2]{};
    unsigned int Axis[3]{};

    float (*fx)(int8_t x, int8_t y, float progress); //=z
private:
    Color *colours;

};


#endif //RGBLEDCUBE_GRAPH_H
