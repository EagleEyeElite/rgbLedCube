/*
 * Snake.h
 *
 * Created: 15/01/2019 22:37:28
 *  Author: Conrad
 */


#include "../../interface/interface.h"

#include <avr/io.h>


#ifndef SNAKE_H_
#define SNAKE_H_


void snake();

class Snake {
public:
    Snake();

    void loadSnake(frame &FrameA, float progress);

    float snakeKoo[10][3]{};
    unsigned int length;
    float tale;
    unsigned int hueHead;
    unsigned int hueTale;
private:

}; //Snake

#endif /* SNAKE_H_ */
