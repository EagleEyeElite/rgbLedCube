#include <math.h>
#include "betweenAxis.h"
#include "../resources/vector/vect.h"
#include "../resources/vector/Plain.h"

static void renderLine(MoveProp *Move, uint8_t lineNr, bool slideIn, float brightness) {
    /*
     * Two animations have to be rendered:
     * 1. the sliding out window from the end to the start pos
     * 2. the sliding in window from the start to the start pos
     * pos makes the selection possible
     */
    float koo[3];
    Position * pos = slideIn ? &Move->startPos : &Move->endPos;
    koo[pos->axis] = pos->side ? 3 - lineNr : 1 + lineNr;
    pos= slideIn ? &Move->endPos : &Move->startPos;
    koo[pos->axis] = pos->side ? 3 : 1;

    uint8_t rgb[3];
    rgb[0] = roundf(Move->Colour->rgb[0] * brightness);
    rgb[1] = roundf(Move->Colour->rgb[1] * brightness);
    rgb[2] = roundf(Move->Colour->rgb[2] * brightness);
    for (unsigned int i = 1; i <= 3; i++) {
        koo[Move->unusedAxis.crossAxis] = i;
        Move->panelFrame->addLight(koo, rgb);
    }
}


void slide(MoveProp *Move) {
    float progress = Move->Watch->getProgress() * 3;

    for (unsigned int i = 1; i <= 2 - progress; i++) {   //fade out
        renderLine(Move, i, false, 1);
    }
    if(progress <= 2.0) {
        renderLine(Move,
                   uint8_t(3 - progress),
                   false,
                   1 - (progress - (uint8_t) progress));
    }
    for (unsigned int i = 0; i <= progress - 1; i++) { // fadi in
        renderLine(Move, i, true, 1);
    }
    renderLine(Move,
               uint8_t(progress),
               true,
               progress > 1.0 ? progress - (uint8_t) progress : 1);
}


void rotatePlain(MoveProp *Move) {
    vect support(2, 2, 2);
    vect directionA(0, 0, 0);
    vect directionB(0, 0, 0);
    Plain plain(support, directionA, directionB);

    float progress = Move->Watch->getProgress();

    plain.direction[0]->Matrix[Move->unusedAxis.crossAxis] = 1;
    plain.support->Matrix[Move->startPos.axis] = Move->startPos.side ? 3 : 1;
    plain.support->Matrix[Move->endPos.axis] = Move->endPos.side ? 3 : 1;

    int8_t direction = 1;
    if (Move->startPos.side != Move->endPos.side)
        direction = -1;

    if (progress < 0.5) {
        plain.direction[1]->Matrix[Move->startPos.axis] = (float) (2 * direction) * progress;
        plain.direction[1]->Matrix[Move->endPos.axis] = 1;
    } else {
        plain.direction[1]->Matrix[Move->startPos.axis] = 1;
        plain.direction[1]->Matrix[Move->endPos.axis] = (float) (-2 * direction) * (progress - 1);
    }
    plain.loadPlain(*Move->panelFrame, Move->Colour);
}
