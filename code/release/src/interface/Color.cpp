/* 
* Color.cpp
*
* Created: 03/10/2018 17:39:37
* Author: Conrad
*/


#include "Color.h"
#include "../hardware/fast_hsv2rgb.h"


// default constructor
Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
} //Color

Color::Color() {
    rgb[0] = 255;
    rgb[1] = 255;
    rgb[2] = 255;
} //Color

void Color::loadRGB(uint8_t r, uint8_t g, uint8_t b) {
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

void Color::loadHSV(uint16_t h, uint8_t s, uint8_t v) {    //h(hue) angle in degrees, s and v from 0 to 255
    uint16_t hue = h * (1535 / 359);
    fast_hsv2rgb_8bit(hue, s, v, &rgb[0], &rgb[1], &rgb[2]);
}

// default destructor
Color::~Color() = default; //Color
