//
// Created by ckl on 14/03/2022.
//

#include <stdint.h> // NOLINT
#include "../../interface/Clock.h"
#include "../../interface/Frame.h"
#include "../../interface/Color.h"

#ifndef RGBLEDCUBE_STRUCTS_H
#define RGBLEDCUBE_STRUCTS_H


struct Position {
    uint8_t axis; // may be 0 for x, 1 for y, or 2 for z
    bool side; // false for side closer to origin, true for opposite
};

enum AnimationPlay { endPosition = 0, rotate = 1, slidePlain = 2, push2 = 3, crumble = 4 };


/**
 * stores all the meta data for the transition movements.
 * The animation stores the animation to be played.
 * Special meta data associated with an animation can be stored in animationInfos, such as the
 * stop points for the crumble animation.
 * Sometimes it good to know which axes are used, for a transition:
 * The used Axis are found in the start and end pos.
 * The unused Axis are in the unused Axis union. For animation on the same axis the crossPlain is used, for animations,
 * that change between two axes, the cross Axis is used.
 */
struct MoveProp {
    Clock *Watch;
    Frame *panelFrame;
    Color *Colour;
    Position startPos;
    Position endPos;
    union {
        int crossAxis;
        int crossPlain[2];
    } unusedAxis;
    AnimationPlay animation;
    union {
        uint8_t crumbleStop[9];
    } animationInfos;
};


#endif //RGBLEDCUBE_STRUCTS_H
