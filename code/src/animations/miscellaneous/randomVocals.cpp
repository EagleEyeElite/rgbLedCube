//
// Created by conrad on 3/26/20.
//


#include "../../interface/interface.h"

#include <stdlib.h> //rand

void randomVocals() {
    Clock Watch(100);
    Frame FrameA(true);

    bool vocal[9];

    Color B = Color();
    B.loadHSV((unsigned int) rand() % 360, 255, 255);

    for (bool &i : vocal) {    //place all Vocals (up or down)
        i = static_cast<uint8_t>(rand() % 2);
    }
    for (int n = 0; n < 60; n++) {    //repeat sending for 30 times
        int selectedVocal = rand() % 9;

        float Koo[3];
        while (Watch.getProgress() <= 1) {
            float progress = Watch.getProgress();

            for (int i = 0; i < 9; i++) {    //place all Vocals (up or down)
                Koo[0] = (float) (i % 3) + 1;
                Koo[1] = (float) ((i / 3) % 3) + 1;
                if (i == selectedVocal) {    //calculate height if selected Vocal is rendered
                    if (vocal[selectedVocal])    //if Selected vocal is at top, reverse Progress to let it descend
                        Koo[2] = (progress * (-2)) + 3;
                    else
                        Koo[2] = (progress * 2) + 1;
                } else {
                    Koo[2] = (float) (vocal[i] * 2) + 1;    //rand 1 or 3
                }
                FrameA.addLight(Koo, B.rgb);
            }
            FrameA.showFrame();
            FrameA.resetFrame();

        }
        Watch.resetTimer();
        vocal[selectedVocal] = !vocal[selectedVocal];

        while (Watch.getProgress() <= 2) {    //render steady image
            for (int i = 0; i < 9; i++) {    //place all Vocals (up or down)
                Koo[0] = (float) (i % 3) + 1;
                Koo[1] = (float) ((i / 3) % 3) + 1;
                Koo[2] = (float) (vocal[i] * 2) + 1;
                FrameA.addLight(Koo, B.rgb);
            }
            FrameA.showFrame();
            FrameA.resetFrame();
        }
        Watch.resetTimer();
    }
}
