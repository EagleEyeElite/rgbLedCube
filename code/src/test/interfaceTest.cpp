//
// Created by conrad on 3/15/20.
//

#include "interfaceTest.h"
#include "../interface/Clock.h"
#include "../interface/Frame.h"
#include "../interface/Color.h"
#include "../animations/resources/vector/Vec.h"
#include "../animations/resources/vector/Straight.h"
#include "../animations/resources/vector/Plain.h"

void testAll() {
    testAddLed();
    testBrightnessTransition();
    testColour();
    testPreset();
    // TODO doesnt work currently - calcPlainPos might be the issue - test if Grayscale cube got it right
    // testPlain();
    testStraight();
}

void testAddLed() {
    Clock Watch(3000);
    Frame Frame(true);

    while (Watch.getProgress() <= 1) {
        Frame.resetFrame();
        const float koo[] = {Watch.getProgress() + 1, 1, 1};
        const uint8_t light[] = {255, 0, 0};
        Frame.addLight(koo, light);
        Frame.showFrame();
    }
}

void testBrightnessTransition() {
    Clock Watch(1000);
    Frame A(true);
    Color B = Color();
    B.loadHSV(0, 255, 255);

    for (int count = 0; count < 2; count++) {
        while (Watch.getProgress() <= 1) {
            A.resetFrame();
            float z = Watch.getProgress() * 2 + 1;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    float koo[3] = {(float) x + 1, (float) y + 1, z};
                    A.addLight(koo, B.rgb);
                }
            }
            A.showFrame();
        }
        Watch.resetTimer();
        while (Watch.getProgress() <= 1) {
            A.resetFrame();
            float z = 3 - (Watch.getProgress() * 2);
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    float koo[3] = {(float) x + 1, (float) y + 1, z};
                    A.addLight(koo, B.rgb);
                }
            }
            A.showFrame();
        }
        Watch.resetTimer();
    }
}

void testColour() {
    Clock Watch(3000);
    Frame A(true);
    Color B = Color();
    float Koo[3] = {2, 2, 2};

    while (Watch.getProgress() <= 1) {
        A.resetFrame();
        B.loadHSV(static_cast<uint16_t>(Watch.getProgress() * 360), 255, 255);
        A.addLight(Koo, B.rgb);
        A.showFrame();
    }
    A.resetFrame();
}

void testPreset() {
    Clock Watch(1000);
    Frame Preset(false);

    while (Watch.getProgress() <= 1) {
        Preset.resetFrame();
        Preset.loadImage(1);
        Preset.showFrame();
    }
}

void testBenchmarkSpeed() {
    Frame A(true);
    A.resetFrame();
    float Koo[3] = {2, 2, 2};
    Color B = Color();
    B.loadHSV(0, 255, 255);

    for (unsigned int i = 0; i < 80; i++) {
        A.addLight(Koo, B.rgb);
    }
}


void testStraight() {
    Clock Watch(4000);
    Frame Frame(true);

    Vec Support(2, 6, 2);
    Vec Direction(0, -1, -1);
    Straight as(Support, Direction);

    while (Watch.getProgress() <= 1) {
        Direction.Matrix[2] = ((Watch.getProgress()) * 2) - 1;
        as.loadStraight(Frame);
        Frame.showFrame();
        Frame.resetFrame();
    }
}


void testPlain() {
    Clock Watch(4000);
    Frame Frame(true);

    Vec Support(2, 6, 2);
    Vec Direction1(1, 0, 0);
    Vec Direction2(0, -1, -1);
    Plain as(Support, Direction1, Direction2);
    Color Colour = Color();

    while (Watch.getProgress() <= 1) {
        Direction2.Matrix[2] = ((Watch.getProgress()) * 2) - 1;
        as.loadPlain(Frame, &Colour);
        Frame.showFrame();
        Frame.resetFrame();
    }

}
