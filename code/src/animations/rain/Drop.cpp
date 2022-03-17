/* 
* Drop.cpp
*
* Created: 15/10/2018 11:23:54
* Author: Conrad
*/


#include "Drop.h"

#include "../../interface/interface.h"

#include <stdlib.h> //rand
#include <math.h>

// default constructor

Drop::Drop() {
    border = (float) (rand() / ((RAND_MAX / 6.0)) + 3);
    dropSpeed = (float) (rand() / ((RAND_MAX / 3.0) + 1.5));
    preStart = 0;
    koo[0] = 2;
    koo[1] = 2;
    koo[2] = border;
} //Drop

void Drop::loadRain(Frame &cubeFrame, float progress) {

    koo[2] = border - ((float) (pow((progress - preStart) * 1.2 * dropSpeed, 2)));

    if (koo[2] < 0) {   // if under the cube
        preStart = progress;    // reset Drop
        border = (float) (rand()) / ((float) (RAND_MAX / 3.0)) + 9;
        dropSpeed = (float) (rand()) / ((float) (RAND_MAX / 1.0)) + 1;

        return;
    }

    if (koo[2] < 4) // if Drop inside cube
        cubeFrame.addLight(koo, rain->rgb);
}
