/* 
* clock.h
*
* Created: 30/09/2018 23:33:17
* Author: Conrad
*/

#include <avr/io.h>

#ifndef __CLOCK_H__
#define __CLOCK_H__


class clock {
public:
    explicit clock(uint16_t maxMillis);

    float getProgress();

    void resetTimer();
    //void pauseStopWatch();
    //void resumeStopWatch();
private:
    uint32_t counterStart;
    uint32_t maxTicks;

}; //clock

void delay(uint16_t time);    // max 65sec

// measures time needed for one calculation (do not use in while loop, EEPROM would run out)
//record the frame rate during an animation -> to get the time, use /miscellaneous/benchmarkResult.py
void benchmark(void (*f)(), uint16_t run_cycles);

//TODO add benchmark to measure FPS frames

#endif //__CLOCK_H__
