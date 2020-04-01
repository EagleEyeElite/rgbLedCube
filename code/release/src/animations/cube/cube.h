//
// Created by conrad on 3/18/20.
//


#include "../resources/vector/vect.h"
#include "../../interface/interface.h"
#include <avr/io.h>

#ifndef RGBLEDCUBE_CUBE_H
#define RGBLEDCUBE_CUBE_H


void createCube();

class cube {
public:
    cube(vect &supportA, float sizeA);

    void loadCube(frame &cubeFrame);

    vect *support;
    float size;
    bool direction[3]{};
private:
    unsigned int hue;
};


#endif //RGBLEDCUBE_CUBE_H
