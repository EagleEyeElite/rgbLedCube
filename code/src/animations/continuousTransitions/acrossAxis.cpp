#include "acrossAxis.h"
#include "../../interface/Color.h"
#include "../../interface/Frame.h"
#include "structs.h"


void push(MoveProp *Move) {
    float progress = Move->Watch->getProgress();
    float koo[3];
    koo[Move->startPos.axis] = Move->startPos.side ? 3 - 2 * progress : 1 + 2 * progress;
    for (unsigned int x = 1; x <= 3; x++) {
        for (unsigned int y = 1; y <= 3; y++) {
            koo[Move->unusedAxis.crossPlain[0]] = x;
            koo[Move->unusedAxis.crossPlain[1]] = y;
            Move->panelFrame->addLight(koo, Move->Colour->rgb);
        }
    }
}

/**
 * Renders pos of a move
 */
void renderEndPos(MoveProp *Move) {
    float koo[3];
    uint8_t plainAxis[] = {
            (uint8_t) (( Move->endPos.axis + 1) % 3),
            (uint8_t) (( Move->endPos.axis + 2) % 3),
    };

    for (unsigned int x = 1; x <= 3; x++) {
        for (unsigned int y = 1; y <= 3; y++) {
            koo[plainAxis[0]] = x;
            koo[plainAxis[1]] = y;
            koo[ Move->endPos.axis] =  Move->endPos.side ? 3 : 1;
            Move->panelFrame->addLight(koo, Move->Colour->rgb);
        }
    }
}

void build(MoveProp *Move) {
    float progress = Move->Watch->getProgress();
    float koo[3];
    for (unsigned int x = 0; x <= 2; x++) {
        for (unsigned int y = 0; y <= 2; y++) {
            koo[Move->unusedAxis.crossPlain[0]] = x + 1;
            koo[Move->unusedAxis.crossPlain[1]] = y + 1;
            float temp;
            if (progress < 0.5) {
                float upperLimit = Move->animationInfos.crumbleStop[y * 3 + x];
                temp = progress * 4 >= upperLimit ? upperLimit : progress * 4;
            } else {
                auto currentHeight = float (Move->animationInfos.crumbleStop[y * 3 + x] + (progress - 0.5) * 4);
                temp = currentHeight >= 2 ? 2 : currentHeight;
            }
            koo[Move->startPos.axis] = Move->startPos.side ? 3 - temp : 1 + temp;
            Move->panelFrame->addLight(koo, Move->Colour->rgb);
        }
    }
}
