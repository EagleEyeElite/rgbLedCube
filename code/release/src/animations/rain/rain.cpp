//
// Created by conrad on 3/24/20.
//

#include <stdlib.h>
#include "../../interface/interface.h"
#include "drop.h"

void rain() {
    clock Watch(8000);
    frame FrameA(true);

    drop Rain[9];
    unsigned int hue = (unsigned int) rand() % 360;
    for (unsigned int i = 0; i < 9; i++) {
        Rain[i].koo[0] = (float) (i % 3) + 1;
        Rain[i].koo[1] = (float) ((i / 3) % 3) + 1;

        auto *s = (colour *) malloc(sizeof(colour));
        *s = colour();
        (*s).loadHSV(hue, (uint8_t) (100 + (rand() % 155)), 255);
        Rain[i].rain = s;
    }

    while (Watch.getProgress() <= 3) {
        float progress = Watch.getProgress() * 8;
        FrameA.resetFrame();
        for (auto &i : Rain) {
            i.loadRain(FrameA, progress);
        }
        FrameA.showFrame();
    }
    for (auto &i : Rain) {
        free(i.rain);
    }

}
