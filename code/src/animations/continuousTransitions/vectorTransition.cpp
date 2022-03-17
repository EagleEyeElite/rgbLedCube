/*
 * rotations.cpp
 *
 * Created: 18/01/2019 00:39:07
 *  Author: Conrad
 */

#include "../resources/vector/Vec.h"
#include "../resources/vector/Straight.h"
#include "../resources/vector/Plain.h"

#include <stdlib.h> //rand

void rotatingStraight() {
    Frame straightFrame(true);
    Clock Watch(400);

    Vec support(1, 1, 1);
    Vec direction(0, 0, 0);
    Straight as(support, direction);

    unsigned int dir[2];
    dir[0] = (unsigned int) rand() % 3;
    dir[1] = (unsigned int) rand() % 3;
    direction.Matrix[dir[1]] = 1;

    for (float &i : support.Matrix) {
        i = (float) (1 + ((rand() % 2) * 2));
    }
    for (unsigned int i = 0; i < 20; i++) {

        while (dir[0] == dir[1])
            dir[0] = (unsigned int) rand() % 3;

        int correction = 1;
        if (support.Matrix[dir[0]] != support.Matrix[dir[1]])
            correction = -1;

        for (unsigned int n = 0; n < 2; n++) {
            while (Watch.getProgress() <= 0.5) {
                if (n == 0)
                    direction.Matrix[dir[n]] = Watch.getProgress() * 2 * (float) correction;
                else
                    direction.Matrix[dir[n]] = (Watch.getProgress() * 2 * -(float) correction) + (float) correction;

                as.loadStraight(straightFrame);
                straightFrame.showFrame();
            }
            direction.Matrix[dir[n]] = (float) (1 - n);
            Watch.resetTimer();
        }
        //support 1 -> 3; 3-> 1
        support.Matrix[dir[0]] = (float) (((unsigned int) (support.Matrix[dir[0]]) % 3) * 2) + 1;
        dir[1] = dir[0];

        while (Watch.getProgress() * 1.5 <= 1) {
            as.loadStraight(straightFrame);
            straightFrame.showFrame();
        }
        Watch.resetTimer();
    }
}
