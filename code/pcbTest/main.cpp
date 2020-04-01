/*
 * TestPCB.cpp
 *
 * Created: 17.08.2018 13:34:47
 * Author : Conrad
 */ 

// #define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>

#define BLANK 0	//PD0
#define VPRG 1	//PD1
#define SIN 3	//PD3	//set
#define SCLK 4	//PD4	//set
#define GSCLK 5	//PD5	//OC1A
#define XLAT 6	//PD6

void inbuilt_LED();

int main(void)
{
    inbuilt_LED();

    DDRC = 0b00000111;    // mosfet -Output
    DDRD |= (1 << BLANK) | (1 << VPRG) | (1 << SIN) | (1 << SCLK) | (1 << GSCLK) | (1 << XLAT);    // define as output
	
    while (true)
    {
        PORTD |= (1 << BLANK) | (1 << VPRG) | (1 << SIN) | (1 << SCLK) | (1 << GSCLK) | (1 << XLAT);    // high
		PORTC = 0b00000000;	// mosfet -high (inverted)
		//for(int i=0; i<=3; i++)
			_delay_us(10);
        PORTD &= ~((1 << BLANK) | (1 << VPRG) | (1 << SIN) | (1 << SCLK) | (1 << GSCLK) | (1 << XLAT));    // low
		PORTC = 0b00000111;	// mosfet -low (inverted)
		//for(int i=0; i<=3; i++)
			_delay_us(10);
    }
}


void inbuilt_LED() {
    DDRD = 0b10000000;    // led -Output
    PORTD = 0b10000000;    // led -High
}
