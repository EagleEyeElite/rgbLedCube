/*
 * plain.h
 *
 * Created: 18/01/2019 00:25:11
 *  Author: Conrad
 */

#include "vect.h"
#include "../../../interface/interface.h"
#include <avr/io.h>

#ifndef PLAIN_H_
#define PLAIN_H_

class plain {
public:
    plain(vect &support, vect &directionX, vect &directionBX);

    void loadPlain(frame &plainFrame, uint8_t brightness);

    vect *support;
    vect *direction[2]{};
private:

}; //plain


#endif /* PLAIN_H_ */