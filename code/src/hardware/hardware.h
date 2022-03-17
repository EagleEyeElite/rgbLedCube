/*
 * hardware.h
 *
 * Created: 02/10/2018 16:37:37
 *  Author: Conrad
 *
 *
 * TIMER0: latches and enable layer data upload
 * TIMER1: GSCLK
 * TIMER2: indicator status led PWM
 * TIMER3: global timer / Clock
 * SPI: code upload
 * USART1: layer data upload
 * INT0: IR-receiver
 * INT2: button
 */
#ifndef HARDWARE_H_
#define HARDWARE_H_
#ifdef __cplusplus
extern "C" {
#endif


#include <avr/interrupt.h>


#define BLANK 0 //PD0
#define VPRG 1  //PD1
#define IR_Rec 2    //PD2
#define SIN 3   //PD3
#define SCLK 4  //PD4
#define GSCLK 5 //PD5	//OC1A
#define XLAT 6  //PD6

#define SW 2    //PB2


// generalHardware
void hardwareSetup();

ISR (INT0_vect, ISR_NOBLOCK);   // IR-receiver
ISR (INT2_vect, ISR_NOBLOCK);   // button

// timer
void timerSetup();
void stopTimer();

ISR(TIMER3_OVF_vect, ISR_BLOCK);    // global timer / Clock

uint32_t getTimerTick();

void resetTimer();

// tlcController
void TLCSetup();
void tlcStop();

ISR(USART1_UDRE_vect, ISR_BLOCK);   // layer data upload

ISR(TIMER0_COMPA_vect, ISR_BLOCK);  // latches and enable layer data upload

void updateDisplay(const uint8_t image[81]);

#ifdef __cplusplus
}
#endif
#endif /* HARDWARE_H_ */
