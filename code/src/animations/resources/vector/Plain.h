/*
 * Plain.h
 *
 * Created: 18/01/2019 00:25:11
 *  Author: Conrad
 */

#include "Vec.h"
#include "../../../interface/interface.h"
#include <avr/io.h>

#pragma once

class Plain {
public:
    Plain(Vec &support, Vec &directionX, Vec &directionBX);

    void loadPlain(Frame &plainFrame, Color *Colour);

    Vec *support;
    Vec *direction[2]{};
private:

}; //Plain
