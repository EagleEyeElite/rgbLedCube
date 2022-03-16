/*
 * slide.cpp
 *
 * Created: 18/01/2019 00:39:16
 *  Author: Conrad
 */

#include <stdlib.h>


#include "../resources/vector/vect.h"
#include "../resources/vector/Straight.h"
#include "../resources/vector/Plain.h"
#include "structs.h"
#include "betweenAxis.h"
#include "acrossAxis.h"

/**
 * Configures the MoveProp for the next move.
 * Depending if the same Axis is used for the transition, two different setup are used.
 * @param Move
 * @param sameAxis
 */
static void generateAxis(MoveProp *Move, bool sameAxis) {
    if (sameAxis) {
        // generate new endPos on same axis on opposite site
        Move->endPos.axis = Move->startPos.axis;
        Move->unusedAxis.crossPlain[0] = (Move->startPos.axis + 1) % 3;
        Move->unusedAxis.crossPlain[1] = (Move->startPos.axis + 2) % 3;
        Move->endPos.side = !Move->startPos.side;
    } else {
        // generate new endPos to another axis
        bool adder = rand() % 2;
        Move->endPos.axis = (Move->startPos.axis + (adder ? 1 : 2)) % 3;
        Move->unusedAxis.crossAxis = (Move->startPos.axis + (adder ? 2 : 1)) % 3;
        Move->endPos.side = rand() % 2;
    }
}


/**
 * Generates new moves for the Plain Transitions
 * There are two types: transitions that happen along the same main axis,
 * and transitions the move to another axis.
 *
 * @param Move stores all the meta data for the move
 */
static void generateNewEndPos(MoveProp *Move) {
    switch (rand() % 4) {
        case 0:
            generateAxis(Move, true);
            for (unsigned char &i: Move->animationInfos.crumbleStop) {
                i = static_cast<uint8_t>(rand() % 3);
            }
            Move->animation = crumble;
            break;
        case 1:
            generateAxis(Move, true);
            Move->animation = push2;
            break;
        case 2:
            generateAxis(Move, false);
            Move->animation = slidePlain;
            break;
        case 3:
            generateAxis(Move, false);
            Move->animation = rotate;
            break;
        default:
            generateAxis(Move, false);
            Move->animation = rotate;
    }
}

static void render(MoveProp *Move) {
    void (*p[5])(MoveProp *) = {renderEndPos, rotatePlain, slide, push, build};
    while (Move->Watch->getProgress() <= 1) {
        Move->panelFrame->resetFrame();
        p[Move->animation](Move);
        Move->panelFrame->showFrame();
    }
    Move->Watch->resetTimer();
}


void panelAnimation() {
    Clock Watch(300);
    Frame panelFrame(true);
    Color Colour = Color();
    Colour.loadHSV(rand() % 360, 0xFF, 0xFF);
    struct MoveProp CurrentMove = {
            &Watch,
            &panelFrame,
            &Colour
    };
    CurrentMove.startPos.axis = rand() % 3;
    CurrentMove.startPos.side = rand() % 2;

    for (unsigned int i = 0; i <= 40; i++) {
        generateNewEndPos(&CurrentMove);
        render(&CurrentMove);
        CurrentMove.animation = endPosition;
        render(&CurrentMove);
        CurrentMove.startPos.axis = CurrentMove.endPos.axis;
        CurrentMove.startPos.side = CurrentMove.endPos.side;
    }
}
