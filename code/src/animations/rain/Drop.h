/* 
* Drop.h
*
* Created: 15/10/2018 11:23:54
* Author: Conrad
*/

#include "../../interface/interface.h"

#include <avr/io.h>

#pragma once

void rain();

class Drop {
//variables
public:
    float koo[3] {};
    Color *rain{};
private:

    float border;
    float dropSpeed;
    float preStart;

//functions
public:
    Drop();

    void loadRain(Frame &cubeFrame, float progress);

}; //Drop
