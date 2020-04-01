/* 
* colour.h
*
* Created: 03/10/2018 17:39:37
* Author: Conrad
*/

#include <avr/io.h>
#include "../hardware/fast_hsv2rgb.h"

#ifndef __COLOUR_H__
#define __COLOUR_H__


class colour {
public:
    colour(uint8_t red, uint8_t green, uint8_t blue);
    colour();

    uint8_t rgb[3]{};
    void loadRGB(uint8_t red, uint8_t green, uint8_t blue);    //Values from 0 to 255
    void loadHSV(uint16_t hue, uint8_t saturation, uint8_t value);    //h(hue) angle in degrees, s and v from 0 to 255
    //void loadHSB();
    ~colour();

private:

}; //colour

#endif //__COLOUR_H__
