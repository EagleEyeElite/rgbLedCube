/*
 * snake.cpp
 *
 * Created: 15/01/2019 22:29:56
 *  Author: Conrad
 */


#include "snake.h"

#include <stdlib.h> //rand

void snake() {
    frame FrameA(false);
    Snake A;
    clock Watch(100);

    for (unsigned int i = 0; i < 300; i++) {    // max led snake will move

        bool direction[6] = {true, true, true, true, true, true}; // all direction head could move to

        for (unsigned int t = 0; t <= A.length - 2; t++) {
            for (unsigned int n = 0; n <= 2; n++) {
                A.snakeKoo[A.length - 1 - t][n] = A.snakeKoo[A.length - 2 - t][n];
            }
        }

        // check all possible directions
        unsigned int countPos = 0;
        for (unsigned int d = 0; d < 6; d++) {
            float temp[3] = {A.snakeKoo[0][0], A.snakeKoo[0][1], A.snakeKoo[0][2]};
            if (d % 2 == 1)
                temp[d / 2] -= 1;
            else
                temp[d / 2] += 1;

            if (3 < temp[d / 2] || temp[d / 2] < 1) {   // direction is not in cube
                direction[d] = false;
            }
            for (unsigned int t = 1; t < A.length && direction[d]; t++) {
                if (A.snakeKoo[t][0] == temp[0] && A.snakeKoo[t][1] == temp[1] && A.snakeKoo[t][2] == temp[2])
                    direction[d] = false;   // direction would hit own snake
            }

            // count possible directions
            if (direction[d])
                countPos++;
        }

        // select direction, move Head
        if (countPos > 0) {
            unsigned int pos = rand() % countPos;
            for (unsigned int d = 0; d <= pos; d++) { // get nth valid position
                if (!direction[d])
                    pos++;
            }
            if (pos % 2 == 1) {
                A.snakeKoo[0][pos / 2] -= 1;
            } else {
                A.snakeKoo[0][pos / 2] += 1;
            }
        } else {    // snake cant go anywhere and is stuck
            delay(600);
            return;
        }

        while (Watch.getProgress() <= 1) {
            A.loadSnake(FrameA, Watch.getProgress());
            FrameA.showFrame();
        }
        Watch.resetTimer();
    }
}
