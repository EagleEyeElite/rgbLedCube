/* 
* Drop.h
*
* Created: 15/10/2018 11:23:54
* Author: Conrad
*/

#include "../../interface/interface.h"

#include <avr/io.h>

#ifndef __DROP_H__
#define __DROP_H__

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

#endif //__DROP_H__
