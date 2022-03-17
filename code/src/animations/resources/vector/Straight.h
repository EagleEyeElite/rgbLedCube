/*
 * Straight.h
 *
 * Created: 18/01/2019 00:25:26
 *  Author: Conrad
 */

#include "Vec.h"
#include "../../../interface/interface.h"
#include <avr/io.h>

#ifndef STRAIGHT_H_
#define STRAIGHT_H_

class Straight {
public:
    Straight(Vec &support, Vec &directionA);

    ~Straight();

    void loadStraight(Frame &straightFrame);

private:
    Vec *support{};
    Vec *direction{};

    Color *colours;
};

#endif /* STRAIGHT_H_ */