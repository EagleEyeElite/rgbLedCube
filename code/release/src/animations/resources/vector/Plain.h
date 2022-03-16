/*
 * Plain.h
 *
 * Created: 18/01/2019 00:25:11
 *  Author: Conrad
 */

#include "vect.h"
#include "../../../interface/interface.h"
#include <avr/io.h>

#ifndef PLAIN_H_
#define PLAIN_H_

class Plain {
public:
    Plain(vect &support, vect &directionX, vect &directionBX);

    void loadPlain(Frame &plainFrame, Color *Colour);

    vect *support;
    vect *direction[2]{};
private:

}; //Plain


#endif /* PLAIN_H_ */