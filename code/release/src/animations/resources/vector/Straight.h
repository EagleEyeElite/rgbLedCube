/*
 * Straight.h
 *
 * Created: 18/01/2019 00:25:26
 *  Author: Conrad
 */

#include "vect.h"
#include "../../../interface/interface.h"
#include <avr/io.h>

#ifndef STRAIGHT_H_
#define STRAIGHT_H_

class Straight {
public:
    Straight(vect &support, vect &directionA);

    ~Straight();

    void loadStraight(Frame &straightFrame);

private:
    vect *support{};
    vect *direction{};

    Color *colours;
};

#endif /* STRAIGHT_H_ */