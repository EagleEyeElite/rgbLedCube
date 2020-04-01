/* 
* drop.h
*
* Created: 15/10/2018 11:23:54
* Author: Conrad
*/

#include "../../interface/interface.h"

#include <avr/io.h>

#ifndef __DROP_H__
#define __DROP_H__

void rain();

class drop {
//variables
public:
    float koo[3] {};
    colour *rain{};
private:

    float border;
    float dropSpeed;
    float preStart;

//functions
public:
    drop();

    void loadRain(frame &cubeFrame, float progress);

}; //drop

#endif //__DROP_H__
