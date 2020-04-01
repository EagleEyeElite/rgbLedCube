/*
 * snake.cpp
 *
 * Created: 15/01/2019 22:37:48
 *  Author: Conrad
 */

#include "snake.h"

#include "../../interface/interface.h"

#include <stdlib.h> //rand

// default constructor
Snake::Snake() {
    length = 10;
    tale = 0.7;

    for (unsigned int n = 0; n < 3; n++) {
        int r = rand() % 3 + 1;
        for (unsigned int d = 0; d <= length - 1; d++) {
            snakeKoo[d][n] = (float) r;
        }
    }

    hueHead = (unsigned int) rand() % 300;
    hueTale = hueHead + 60;

} //Snake

void Snake::loadSnake(frame &FrameA, float progress) {
    FrameA.resetFrame();
    colour B = colour();
    auto taleLength = (unsigned int) (tale * (float) length);

    B.loadHSV(hueHead, 255, (uint8_t) (progress * 255));
    FrameA.addLight(snakeKoo[0], B.rgb);    //head
    B.loadHSV(hueHead + (unsigned int) (progress * 60), 255, 255);
    FrameA.addLight(snakeKoo[1], B.rgb);

    B.loadHSV(hueTale, 255, 255);
    for (unsigned int t = 2; t < length - taleLength; t++) {    // body
        FrameA.addLight(snakeKoo[t], B.rgb);
    }
    auto bTale = (unsigned int) ((1 - progress) * (0xFF / (float) taleLength));
    for (unsigned int t = length - taleLength; t <= length - 1; t++) {    // tale
        B.loadHSV(hueTale, 0xFF, (uint8_t) ((0xFF / taleLength) * (-t + length - 1) + bTale));
        FrameA.addLight(snakeKoo[t], B.rgb);
    }
}
