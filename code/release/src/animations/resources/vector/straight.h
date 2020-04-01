/*
 * straight.h
 *
 * Created: 18/01/2019 00:25:26
 *  Author: Conrad
 */

#include "vect.h"
#include "../../../interface/interface.h"
#include <avr/io.h>

#ifndef STRAIGHT_H_
#define STRAIGHT_H_

class straight {
public:
    straight(vect &support, vect &directionA);

    ~straight();

    void loadStraight(frame &straightFrame);

private:
    vect *support{};
    vect *direction{};

    colour *colours;
};

#endif /* STRAIGHT_H_ */