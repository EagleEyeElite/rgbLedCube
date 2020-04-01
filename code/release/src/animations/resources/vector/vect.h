/*
 * vect.h
 *
 * Created: 18/01/2019 00:25:03
 *  Author: Conrad
 */

#include "../../../interface/interface.h"

#ifndef VEKTOR_H_
#define VEKTOR_H_


class vect {
public:
    vect(float x, float y, float z);

    void loadVector(frame &vectorFrame, uint8_t brightness);

    float Matrix[3]{};
private:

};

void moveSupport(float *support, const float *directionOrig);

void calcLimit(int8_t limit[], const float support[], float direction[]);

void calcPlainPos(float supportReturn[], const float supportOrig[], const float directionA[], const float directionB[]);

#endif /* VEKTOR_H_ */
