/*
 * slide.cpp
 *
 * Created: 18/01/2019 00:39:16
 *  Author: Conrad
 */


#include "../../interface/interface.h"

#include "../resources/vector/vect.h"
#include "../resources/vector/straight.h"
#include "../resources/vector/plain.h"

#include <avr/io.h>
#include <stdlib.h> //rand

static void
playAnimationsA(void (*f)(float, frame *, uint8_t [], uint8_t[], uint8_t[], float[], uint8_t []), clock *Watch,
                frame *panelFrame, uint8_t startPos[3], uint8_t endPos[3], uint8_t axis[3], float koo[3],
                uint8_t stop[9]);

static void
push(float progress, frame *panelFrame, const uint8_t startPos[3], uint8_t, const uint8_t axis[3],
     float koo[3],
     uint8_t);

static void
slide(float progress, frame *panelFrame, const uint8_t startPos[3], const uint8_t endPos[3], const uint8_t axis[3],
      float koo[3],
      uint8_t);

static void
build(float progress, frame *panelFrame, const uint8_t startPos[3], uint8_t, const uint8_t axis[3],
      float koo[3],
      const uint8_t stop[9]);

static void
rotatePlain(float progress, frame *panelFrame, const uint8_t startPos[3], const uint8_t endPos[3],
            const uint8_t axis[3], float,
            uint8_t);

static void
showEndPos(float, frame *panelFrame, uint8_t, const uint8_t endPos[3], const uint8_t axis[3],
           float koo[3],
           uint8_t);

void panelAnimation() {
    clock Watch(400);
    frame panelFrame(true);

    float koo[3]{};
    uint8_t startPos[3] = {1, 0, 0};
    uint8_t endPos[3] = {0, 0, 0};
    uint8_t stop[9]{};
    uint8_t axis[3]{};

    for (int x = 0; x < 40; x++) { // iterations
        if (rand() % 2) {
            for (unsigned int i = 0; i < 3; i++) {    // generate new endPos
                if (startPos[i] != 0)
                    endPos[(i + (rand() % 2) + 1) % 3] = static_cast<uint8_t>((rand() % 2) * 2 + 1);
            }

            for (unsigned int i = 0; i < 3; i++) {
                if (startPos[i] == endPos[i])
                    axis[0] = (uint8_t) i;
            }
            axis[1] = (uint8_t) (axis[0] + 1);
            axis[2] = (uint8_t) (axis[0] + 1);
            if (startPos[(axis[0] + 1) % 3] == 0) {
                axis[1] += 1;
            } else {
                axis[2] += 1;
            }
            axis[1] = (uint8_t) (axis[1] % 3);
            axis[2] = (uint8_t) (axis[2] % 3);

            if (rand() % 2)    //rotate
                playAnimationsA(reinterpret_cast<void (*)(float, frame *, uint8_t *, uint8_t *, uint8_t *, float *,
                                                          uint8_t *)>(rotatePlain), &Watch, &panelFrame, startPos,
                                endPos, axis, koo, stop);
            else    //slide
                playAnimationsA(reinterpret_cast<void (*)(float, frame *, uint8_t *, uint8_t *, uint8_t *, float *,
                                                          uint8_t *)>(slide), &Watch, &panelFrame, startPos, endPos,
                                axis, koo, stop);
        } else {
            for (unsigned int i = 0; i < 3; i++) {    // generate new endPos
                if (startPos[i] != 0) {
                    if (startPos[i] == 1)
                        endPos[i] = 3;
                    else
                        endPos[i] = 1;
                }
            }

            for (unsigned int i = 0; i < 3; i++) {
                if (startPos[i] != endPos[i])
                    axis[0] = (uint8_t) i;
            }
            axis[1] = static_cast<uint8_t>((axis[0] + 1) % 3);
            axis[2] = static_cast<uint8_t>((axis[0] + 2) % 3);

            for (unsigned char &i : stop) {
                i = static_cast<uint8_t>(rand() % 3);
            }

            if (rand() % 2) {    //normal push
                playAnimationsA(reinterpret_cast<void (*)(float, frame *, uint8_t *, uint8_t *, uint8_t *, float *,
                                                          uint8_t *)>(push), &Watch, &panelFrame, startPos, endPos,
                                axis,
                                koo, stop);
            } else {    //crumble
                playAnimationsA(reinterpret_cast<void (*)(float, frame *, uint8_t *, uint8_t *, uint8_t *, float *,
                                                          uint8_t *)>(build), &Watch, &panelFrame, startPos, endPos,
                                axis, koo, stop);
            }
        }

        for (unsigned int i = 0; i < 3; i++) {
            if (endPos[i] != 0)
                axis[0] = (uint8_t) i;
        }
        axis[1] = static_cast<uint8_t>((axis[0] + 1) % 3);
        axis[2] = static_cast<uint8_t>((axis[0] + 2) % 3);

        playAnimationsA(reinterpret_cast<void (*)(float, frame *, uint8_t *, uint8_t *, uint8_t *, float *,
                                                  uint8_t *)>(showEndPos), &Watch, &panelFrame, startPos, endPos, axis,
                        koo, stop);

        for (unsigned int i = 0; i < 3; i++) {
            startPos[i] = endPos[i];
            endPos[i] = 0;
        }
    }
}

static void
playAnimationsA(void (*f)(float, frame *, uint8_t [], uint8_t[], uint8_t[], float[], uint8_t []), clock *Watch,
                frame *panelFrame, uint8_t startPos[3], uint8_t endPos[3], uint8_t axis[3], float koo[3],
                uint8_t stop[9]) {
    while ((*Watch).getProgress() <= 1) {
        (*panelFrame).resetFrame();
        f((*Watch).getProgress(), panelFrame, startPos, endPos, axis, koo, stop);
        (*panelFrame).showFrame();
    }
    (*Watch).resetTimer();
}

static void
rotatePlain(float progress, frame *panelFrame, const uint8_t startPos[3], const uint8_t endPos[3],
            const uint8_t axis[3], float,
            uint8_t) {
    vect support(2, 2, 2);
    vect directionA(0, 0, 0);
    vect directionB(0, 0, 0);
    plain plain(support, directionA, directionB);

    plain.direction[0]->Matrix[axis[0]] = 1;
    plain.support->Matrix[axis[1]] = startPos[axis[1]];
    plain.support->Matrix[axis[2]] = endPos[axis[2]];

    int8_t direction = 1;
    if (startPos[axis[1]] != endPos[axis[2]])
        direction = -1;

    if (progress < 0.5) {
        plain.direction[1]->Matrix[axis[1]] = (float) (2 * direction) * progress;
        plain.direction[1]->Matrix[axis[2]] = 1;
    } else {
        plain.direction[1]->Matrix[axis[1]] = 1;
        plain.direction[1]->Matrix[axis[2]] = (float) (-2 * direction) * (progress - 1);
    }
    plain.loadPlain(*panelFrame, 0xFF);
}

static void
slide(float progress, frame *panelFrame, const uint8_t startPos[3], const uint8_t endPos[3], const uint8_t axis[3],
      float koo[3],
      uint8_t) {
    int8_t direction = 1;
    if (endPos[axis[2]] == 1) {
        direction = -1;
    }
    for (unsigned int i = 0; i < 9; i++) {    //fade out
        koo[axis[0]] = (float) (i % 3) + 1;
        koo[axis[1]] = startPos[axis[1]];
        koo[axis[2]] = (progress * 2) * (float) direction + (float) ((int) (i / 3) + 1);
        colour B = colour();
        (*panelFrame).addLight(koo, B.rgb);
    }

    direction = 1;
    if (startPos[axis[1]] == 1) {
        direction = -1;
    }
    for (unsigned int i = 0; i < 9; i++) {    //fade in
        koo[axis[0]] = (float) (i % 3) + 1;
        koo[axis[1]] = (float) ((int) (i / 3) + 1) + (2 - progress * 2) * (float) direction;
        koo[axis[2]] = endPos[axis[2]];
        colour B = colour();
        (*panelFrame).addLight(koo, B.rgb);
    }
}

static void
push(float progress, frame *panelFrame, const uint8_t startPos[3], uint8_t, const uint8_t axis[3],
     float koo[3],
     uint8_t) {
    for (unsigned int i = 0; i < 9; i++) {
        if (startPos[axis[0]] == 3) {
            koo[axis[0]] = 3 - 2 * progress;    //1 + 2*koo[axis[0]] - (2-startPos[axis[0]]*4) *Watch.timerProgress()
        } else {
            koo[axis[0]] = 1 + 2 * progress;
        }
        koo[axis[1]] = (float) (i % 3) + 1;
        koo[axis[2]] = (float) ((int) (i / 3) + 1);
        colour B = colour();
        (*panelFrame).addLight(koo, B.rgb);
    }
}

static void
build(float progress, frame *panelFrame, const uint8_t startPos[3], uint8_t, const uint8_t axis[3],
      float koo[3],
      const uint8_t stop[9]) {
    if (progress < 0.5) {
        progress *= 2;
        int multi = 2 - startPos[axis[0]];
        for (unsigned int i = 0; i < 9; i++) {

            float temp = progress * 2;
            if (temp >= (float) stop[i]) {
                temp = stop[i];
            }
            koo[axis[0]] = (float) startPos[axis[0]] + temp * (float) multi;
            koo[axis[1]] = (float) (i % 3) + 1;
            koo[axis[2]] = (float) ((int) (i / 3) + 1);
            colour B = colour();
            (*panelFrame).addLight(koo, B.rgb);
        }
    } else {
        progress = (progress - (float) 0.5) * 2;
        int multi = 2 - startPos[axis[0]];
        for (unsigned int i = 0; i < 9; i++) {

            float temp = (float) stop[i] + progress * 2;
            if (temp >= 2) {
                temp = 2;
            }
            koo[axis[0]] = (float) startPos[axis[0]] + temp * (float) multi;
            koo[axis[1]] = (float) (i % 3) + 1;
            koo[axis[2]] = (float) ((int) (i / 3) + 1);
            colour B = colour();
            (*panelFrame).addLight(koo, B.rgb);
        }
    }
}

static void
showEndPos(float, frame *panelFrame, uint8_t, const uint8_t endPos[3], const uint8_t axis[3],
           float koo[3],
           uint8_t) {
    for (unsigned int i = 0; i < 9; i++) {
        koo[axis[0]] = endPos[axis[0]];
        koo[axis[1]] = (float) (i % 3) + 1;
        koo[axis[2]] = (float) (i / 3 % 3) + 1;
        colour B = colour();
        (*panelFrame).addLight(koo, B.rgb);
    }
}
