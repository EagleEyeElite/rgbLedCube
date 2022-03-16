//
// Created by conrad on 3/19/20.
//


#include "../resources/vector/vect.h"
#include "../../interface/interface.h"
#include <avr/io.h>

#ifndef RGBLEDCUBE_PLOT_H
#define RGBLEDCUBE_PLOT_H

void infinityFigure();

void circleFigure();


class Plot {
public:
    Plot(vect &coordinateOriginal, float (*fa)(float x), float (*fb)(float y), float (*fc)(float z));

    ~Plot();

    void setAxis(uint8_t x, uint8_t y, uint8_t z);

    void loadPoint(Frame &FrameA, float x);

    vect *coordinate_origin;

    float (*f[3])(float x){};

private:
    Color *colours;
    uint8_t Axis[3]{};

}; //Plot


#endif //RGBLEDCUBE_PLOT_H
