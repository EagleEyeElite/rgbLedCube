/*
 * basic.cpp
 *
 * Created: 03/10/2018 17:04:09
 *  Author: Conrad
 */

#include "../../interface/interface.h"

void defaultImages() {
    Frame A(false);
    A.loadImage(2);
    Frame B(false);
    B.loadImage(1);
    A.addFrame(B);

    A.showFrame();
    delay(2000);
}

void glowingCube() {
    Clock Watch(500);
    Frame FrameA(false);

    while (Watch.getProgress() <= 1) {
        FrameA.resetFrame();
        Color B = Color(0, (uint8_t) (Watch.getProgress() * 0xFF), 0);
        for (uint8_t i = 0; i <= 26; i++) {
            FrameA.addLight(i, B.rgb);
        }
        FrameA.showFrame();
    }
    Watch.resetTimer();
    while (Watch.getProgress() <= 1) {
        FrameA.resetFrame();
        Color B = Color(0, (uint8_t) (0xFF - (Watch.getProgress() * 0xFF)), 0);
        for (uint8_t i = 0; i <= 26; i++) {
            FrameA.addLight(i, B.rgb);
        }
        FrameA.showFrame();
    }
}

void runningLed() {
    Clock Watch(1000);
    Frame Frame(true);

    Color B = Color(200, 180, 100);
    float Koo[3];
    while (Watch.getProgress() <= 1) {
        auto numLed = (unsigned int) (Watch.getProgress() * 28);
        for (unsigned int i = 0; i < numLed; i++) {
            Koo[0] = (float) (i % 3) + 1;
            Koo[1] = (float) ((i / 3) % 3) + 1;
            Koo[2] = (float) ((i / 9) % 3) + 1;
            Frame.addLight(Koo, B.rgb);
        }
        Frame.showFrame();
        Frame.resetFrame();
    }
}

void fadingLed() {
    Clock Watch(500);
    Frame FrameA(false);

    float Koo[3] = {2, 2, 2};
    while (Watch.getProgress() <= 1) {
        Color B = Color((uint8_t) (Watch.getProgress() * 0xFF), 0, 0);
        FrameA.addLight(Koo, B.rgb);
        FrameA.showFrame();
        FrameA.resetFrame();
    }
    Watch.resetTimer();
    while (Watch.getProgress() <= 1) {
        Color B = Color((uint8_t) (0xFF - (Watch.getProgress() * 0xFF)), 0, 0);
        FrameA.addLight(Koo, B.rgb);
        FrameA.showFrame();
        FrameA.resetFrame();
    }
}

void flashingCube() {
    Clock Watch(500);
    Frame FrameA(false);

    for (unsigned int i = 0; i < 27; i++) {
        Color B = Color();
        FrameA.addLight((uint8_t) (i), B.rgb);
    }
    FrameA.showFrame();
    while (Watch.getProgress() <= 1) {}
    Watch.resetTimer();

    for (unsigned int i = 0; i < 27; i++) {
        Color B = Color(0, 0, 0);
        FrameA.addLight((uint8_t) i, B.rgb);
    }
    FrameA.showFrame();
    while (Watch.getProgress() <= 1) {}
}

void stackingLayer() {
    Clock Watch(2000);
    Frame FrameA(false);
    Color B = Color(100, 255, 0);
    float Koo[3];
    while (Watch.getProgress() <= 1) {
        auto height = (unsigned int) (Watch.getProgress() * 4) + 1;
        for (unsigned int layer = 0; layer < height; layer++) {
            Koo[2] = (float) layer;
            for (unsigned int i = 0; i < 9; i++) {
                Koo[0] = (float) (i % 3) + 1;
                Koo[1] = (float) ((i / 3) % 3) + 1;
                FrameA.addLight(Koo, B.rgb);
            }
        }
        FrameA.showFrame();
        FrameA.resetFrame();
    }
}

void redCube() {
    Clock Watch(1000);
    Frame FrameA(false);

    while (Watch.getProgress() <= 1) {
        for (unsigned int i = 0; i < 27; i++) {
            Color B = Color(255, 0, 0);
            FrameA.addLight((uint8_t) i, B.rgb);
        }
        FrameA.showFrame();
        FrameA.resetFrame();
    }
}

void fadeInFadeOut() {
    Clock Watch(2000);
    Frame FrameOrig(false);
    Frame FrameOne(false);
    Frame FrameTwo(false);

    FrameOne.loadImage(1);
    FrameTwo.loadImage(2);

    while (Watch.getProgress() <= 1) {
        FrameOrig.resetFrame();
        float progress = Watch.getProgress();
        for (unsigned int i = 0; i < 27; i++) {
            uint8_t rgb[3]{0, 0, 0};
            FrameOne.getLed(i, rgb);
            rgb[0] *= progress;
            rgb[1] *= progress;
            rgb[2] *= progress;
            FrameOrig.addLight((uint8_t) i, rgb);
            progress = 1 - progress;
            FrameTwo.getLed((uint8_t) i, rgb);
            rgb[0] *= progress;
            rgb[1] *= progress;
            rgb[2] *= progress;
            FrameOrig.addLight((uint8_t) i, rgb);
        }
        FrameOrig.showFrame();
    }
}

void fadePreset() {
    Clock Watch(1000);
    Frame FrameA(false);
    Frame Preset(false);
    Preset.loadImage(1);

    while (Watch.getProgress() <= 1) {
        FrameA.resetFrame();
        float progress = Watch.getProgress();
        for (unsigned int i = 0; i < 27; i++) {
            uint8_t rgb[3]{0, 0, 0};
            Preset.getLed(i, rgb);
            rgb[0] *= progress;
            rgb[1] *= progress;
            rgb[2] *= progress;
            FrameA.addLight((uint8_t) i, rgb);
        }
        FrameA.showFrame();
    }
}
