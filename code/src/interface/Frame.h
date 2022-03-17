/* 
* Frame.h
*
* Created: 02.09.2018 19:28:43
* Author: Conrad
*/

#include <avr/io.h>

#ifndef __FRAME_H__
#define __FRAME_H__


void getImage(unsigned int imageNr, uint8_t image[81]);

class Frame {
public:
    explicit Frame(bool smooth);

    bool smooth;    // sets render option for addLight

    void loadImage(unsigned int imageNr);    // loads image from IMG_preset.h

    void getLed(unsigned int ledNr, uint8_t rgb[3]);

    void addLight(const float *koo, const uint8_t *rgb);

    void addLight(uint8_t ledNr, const uint8_t *rgb);

    void addFrame(Frame Frame_to_add);    // adds a Frame to current Frame
    void resetFrame();

    void showFrame();    // displays Frame
    //~Frame();
private:
    void writeFrame(const uint8_t koo[3], const uint8_t rgb[3]);

    uint8_t ledFrameColours[81]{}; // 24-bit Color resolution
}; //Frame

#endif //__FRAME_H__
