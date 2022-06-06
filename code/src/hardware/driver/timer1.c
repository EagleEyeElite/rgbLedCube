#include "timer1.h"

#include <avr/io.h>

/**
 * Timer 1 generates an clock signal for the Led Driver.
 * GSCKL (Pin PD4) is overwritten by the Timer.
 */
void startGSCLK() {
    // GSCLK (OC1A) Clock generation: waveform generation mode 4: non PWM, CTC, top OCR1A
    // toggle 0C0A on compare match, prescaler = 1, 1.25 MHZ, 800nS per GS-bit
    TCCR1A |= 1 << COM1A0;
    TCCR1B |= 1 << WGM12;
    TCCR1C |= 1 << FOC1A;

    // 20MHZ / (2 * prescaler * ( 1 + OCR1A)) => 1,25MHZ -> a signal is latched every 800 ns
    // interrupt needs to triggered every 3.27 ms.
    OCR1A = 7;
    TCCR1B |= 1 << CS10;    // starts GSCLK
}

/**
 * Releases pin overwrite on GSCLK (PIN PD4).
 * Stops timer.
 */
void stopGSCLK() {
    TCCR1A = 0;
    TCCR1A &= ~(1 << COM1A0);   // lets us control GSCKL, disconnected from Timer 1
    TCCR1B &= ~(1 << CS10); // stops timer 1
}
