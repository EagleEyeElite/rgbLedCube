/* 
* Frame.cpp
*
* Created: 02.09.2018 19:28:43
* Author: Conrad
*/

#include "Frame.h"
#include "img_preset.h"

#include <math.h>
#include <avr/pgmspace.h>

static void safeAdd(uint8_t *frame, uint8_t brightness);

// default constructor
Frame::Frame(bool s) {
    smooth = s;
    resetFrame();
}

// public
void Frame::loadImage(unsigned int imageNr) {
    for (int i = 0; i < 81; i++)
        ledFrameColours[i] = pgm_read_byte(image_Preset[imageNr] + i);
}

void Frame::getLed(unsigned int ledNr, uint8_t rgb[3]) {
    ledNr *= 3;
    rgb[0] = ledFrameColours[ledNr + 0];
    rgb[1] = ledFrameColours[ledNr + 1];
    rgb[2] = ledFrameColours[ledNr + 2];
}

void Frame::addLight(const float *koo, const uint8_t *rgb) {
    uint8_t ledCoordinates[3] = {};    // selects current Led
    if (!smooth) { // fast calc, sharp edges
        for (unsigned int d = 0; d < 3; d++) {    // d = dimension
            ledCoordinates[d] = (uint8_t) roundf(koo[d]);
            if (ledCoordinates[d] < 1 || ledCoordinates[d] > 3)
                return;
        }
        writeFrame(ledCoordinates, rgb);
        return;
    }
    float brightnessFactor[3];    // used for calculation the brightness of nearby led
    for (unsigned int d = 0; d < 3; d++) {
        float f3;
        brightnessFactor[d] = modff(koo[d], &f3);
    }

    for (unsigned int led = 0; led <= 0b111; led++) {    // check all 8 neighbors

        bool pass = true;    // check if ledCoordinates Led is still in the cube
        float ledBrightness = 1;    // ledCoordinates Brightness
        for (unsigned int d = 0; d < 3; d++) {    // d = dimension (x, y, z)
            bool offset = (bool) ((led >> d) & 1u);  // specify which led is meant
            ledCoordinates[d] = ((uint8_t) (koo[d])) + offset;    // select which Led is checked
            if (ledCoordinates[d] < 1 || ledCoordinates[d] > 3 || koo[d] < 0) {
                pass = false;
                break;
            }
            if(offset)
                ledBrightness *= brightnessFactor[d];
            else
                ledBrightness *= 1 - brightnessFactor[d];
        }
        if (!pass) { // skip calculations if led is not in the cube
            continue;
        }
        uint8_t add[3];
        for (unsigned int c = 0; c < 3; c++) {    // c = color channel (rgb)
            add[c] = (uint8_t)((float) rgb[c] * ledBrightness);
        }
        writeFrame(ledCoordinates, add);
    }
}

void Frame::addLight(uint8_t ledNr, const uint8_t *rgb) {
    ledNr *= 3;
    for (int i = 0; i < 3; i++) {
        safeAdd(&ledFrameColours[ledNr + i], rgb[i]);
    }
}

void Frame::addFrame(Frame Frame_to_add) {
    for (int i = 0; i < 81; i++) {
        safeAdd(&ledFrameColours[i], Frame_to_add.ledFrameColours[i]);
    }
}

void Frame::resetFrame() {
    for (unsigned char &i : ledFrameColours)
        i = 0;
}

void Frame::showFrame() {
    updateDisplay(ledFrameColours);
}

//Private
void Frame::writeFrame(const uint8_t koo[3], const uint8_t rgb[3]) {
    auto ledNr = (unsigned int) ((koo[0] - 1) * 3 + (koo[1] - 1) * 9 + (koo[2] - 1) * 27);
    for (unsigned int c = 0; c < 3; c++) {    // c = color channel (rgb)
        safeAdd(&ledFrameColours[ledNr + c], rgb[c]);
    }
}//CubeFrame

static void safeAdd(uint8_t *frame, uint8_t brightness) {
    *frame += brightness;
    if (*frame < brightness) {   // detect overflow
        *frame = 0xFF;
    }
}
