/*
 * tlcController.cpp
 *
 * Created: 02.09.2018 18:57:36
 *  Author: Conrad
 */

#include "hardware.h"

#include <avr/io.h>
#include <avr/interrupt.h>

// look up table:
// linear
static volatile const uint16_t lightness[0x100] =
        {0x000, 0x010, 0x020, 0x030, 0x040, 0x050, 0x060, 0x070, 0x080, 0x091, 0x0a1, 0x0b1, 0x0c1, 0x0d1, 0x0e1, 0x0f1,
         0x101, 0x111, 0x121, 0x131, 0x141, 0x151, 0x161, 0x171, 0x181, 0x191, 0x1a2, 0x1b2, 0x1c2, 0x1d2, 0x1e2, 0x1f2,
         0x202, 0x212, 0x222, 0x232, 0x242, 0x252, 0x262, 0x272, 0x282, 0x292, 0x2a2, 0x2b3, 0x2c3, 0x2d3, 0x2e3, 0x2f3,
         0x303, 0x313, 0x323, 0x333, 0x343, 0x353, 0x363, 0x373, 0x383, 0x393, 0x3a3, 0x3b3, 0x3c4, 0x3d4, 0x3e4, 0x3f4,
         0x404, 0x414, 0x424, 0x434, 0x444, 0x454, 0x464, 0x474, 0x484, 0x494, 0x4a4, 0x4b4, 0x4c4, 0x4d5, 0x4e5, 0x4f5,
         0x505, 0x515, 0x525, 0x535, 0x545, 0x555, 0x565, 0x575, 0x585, 0x595, 0x5a5, 0x5b5, 0x5c5, 0x5d5, 0x5e6, 0x5f6,
         0x606, 0x616, 0x626, 0x636, 0x646, 0x656, 0x666, 0x676, 0x686, 0x696, 0x6a6, 0x6b6, 0x6c6, 0x6d6, 0x6e6, 0x6f7,
         0x707, 0x717, 0x727, 0x737, 0x747, 0x757, 0x767, 0x777, 0x787, 0x797, 0x7a7, 0x7b7, 0x7c7, 0x7d7, 0x7e7, 0x7f7,
         0x808, 0x818, 0x828, 0x838, 0x848, 0x858, 0x868, 0x878, 0x888, 0x898, 0x8a8, 0x8b8, 0x8c8, 0x8d8, 0x8e8, 0x8f8,
         0x908, 0x919, 0x929, 0x939, 0x949, 0x959, 0x969, 0x979, 0x989, 0x999, 0x9a9, 0x9b9, 0x9c9, 0x9d9, 0x9e9, 0x9f9,
         0xa09, 0xa19, 0xa2a, 0xa3a, 0xa4a, 0xa5a, 0xa6a, 0xa7a, 0xa8a, 0xa9a, 0xaaa, 0xaba, 0xaca, 0xada, 0xaea, 0xafa,
         0xb0a, 0xb1a, 0xb2a, 0xb3b, 0xb4b, 0xb5b, 0xb6b, 0xb7b, 0xb8b, 0xb9b, 0xbab, 0xbbb, 0xbcb, 0xbdb, 0xbeb, 0xbfb,
         0xc0b, 0xc1b, 0xc2b, 0xc3b, 0xc4c, 0xc5c, 0xc6c, 0xc7c, 0xc8c, 0xc9c, 0xcac, 0xcbc, 0xccc, 0xcdc, 0xcec, 0xcfc,
         0xd0c, 0xd1c, 0xd2c, 0xd3c, 0xd4c, 0xd5d, 0xd6d, 0xd7d, 0xd8d, 0xd9d, 0xdad, 0xdbd, 0xdcd, 0xddd, 0xded, 0xdfd,
         0xe0d, 0xe1d, 0xe2d, 0xe3d, 0xe4d, 0xe5d, 0xe6e, 0xe7e, 0xe8e, 0xe9e, 0xeae, 0xebe, 0xece, 0xede, 0xeee, 0xefe,
         0xf0e, 0xf1e, 0xf2e, 0xf3e, 0xf4e, 0xf5e, 0xf6e, 0xf7f, 0xf8f, 0xf9f, 0xfaf, 0xfbf, 0xfcf, 0xfdf, 0xfef,
         0xfff};

static volatile uint8_t shiftOutInstruction[3][41];
static volatile uint8_t shiftOutNr = 0;
static volatile uint8_t currentLayer = 0;


// set up TLC controls
void TLCSetup() {
    // PC0-PC2 mosfet-Outputs (inverted)
    PORTC = 0b00000111;    // mosfet - low (inverted)
    DDRC = 0b00000111;    // mosfet - output

    DDRD |= 1u << (unsigned) BLANK | 1u << (unsigned) VPRG | 1u << (unsigned) SIN | 1u << (unsigned) SCLK |
            1u << (unsigned) GSCLK | 1u << (unsigned) XLAT;    // define as output
    PORTD &= ~(1u << (unsigned) BLANK); // high (inverted) - turn off TLC output

    PORTD |= 1u << (unsigned) VPRG;     // DC data input mode
    PORTD |= 1u << (unsigned) SIN;
    PORTD  &= ~(1u << (unsigned) SCLK); // make sure its low
    for (int i = 0; i < 162; i++) {     // 6 bits * 27 channels = 162
        PIND = 1u << (unsigned) SCLK;
        PIND = 1u << (unsigned) SCLK;    // low
    }
    PIND = 1u << (unsigned) XLAT;
    PIND = 1u << (unsigned) XLAT;

    PORTD &= ~(1u << (unsigned) VPRG);  // GS data input mode
    PORTD &= ~(1u << (unsigned) SIN);   // clear all old data

    for (int i = 0; i < 324; i++) {     // 12bits * 27 channels = 324
        PIND = 1u << (unsigned) SCLK;
        PIND = 1u << (unsigned) SCLK;   // low
    }
    PIND = 1u << (unsigned) XLAT;
    PIND = 1u << (unsigned) XLAT;   // low

    PORTD  &= ~(1u << (unsigned) XLAT); // make sure they are low
    PORTD  &= ~(1u << (unsigned) SCLK);
    PORTD |= (1u << (unsigned) BLANK);  // low (inverted) - enable TLC output

    // MSPIM mode: starts USART as SPI: MSPI: SPI-mode 0, MSB, baud rate: 0
    // transmitter enable, USART data register empty interrupt enable
    UBRR1 = 0;
    DDRD |= 1u << (unsigned) SCLK;
    UCSR1C = 1u << (unsigned) UMSEL10 | 1u << (unsigned) UMSEL11;
    UCSR1B |= 1u << (unsigned) TXEN1 | 1u << (unsigned) UDRIE1;
    // defines between interrupts tó update tlc (the less updates = faster code)
    UBRR1 = 95; // 100 is the highest number not breaking

    // GSCLK (OC1A) clock generation: waveform generation mode 4: non PWM, CTC, top OCR1A
    // toggle 0C0A on compare match, prescaler = 1, 1.25 MHZ, 800nS per GS-bit
    TCCR1A |= 1u << (unsigned) COM1A0;
    TCCR1B |= 1u << (unsigned) WGM12;
    TCCR1C |= 1u << (unsigned) FOC1A;
    // 20MHZ / (2 * prescaler * ( 1 + OCR1A)) => 1,25MHZ -> a signal is latched every 800 ns
    // interrupt needs to triggered every 3.27 ms.
    OCR1A = 7;
    TCCR1B |= 1u << (unsigned) CS10;    // starts GSCLK

    // control MSPIM - timer 0 interrupts: CTC mode, timer 0 interrupt on OCR2A, 1024 prescaler
    // interrupt after 3.2768ms, 101.7 hz refresh rate
    TCCR0A |= 1u << (unsigned) WGM01;
    OCR0A = 64;    // prescaler*OCR0A /20MHZ -> interrupt timing
    TIMSK0 |= 1u << (unsigned) OCIE0A;
    TCCR0B |= 1u << (unsigned) CS00 | 1u << (unsigned) CS02;    // start timer
}

ISR(USART1_UDRE_vect, ISR_BLOCK) {    // clocks in data
    if (++shiftOutNr < 41)    // sendLength = 41, (27*12 bits -> 40.5 * 8bits)
        UDR1 = shiftOutInstruction[currentLayer][shiftOutNr];
}

ISR(TIMER0_COMPA_vect, ISR_BLOCK) {    // controls MSPIM upload and cube image
    PIND = 1u << (unsigned) BLANK;    // high (inverted) - resets TLC counter (4096)
    while (!((unsigned) UCSR1A & (1u << (unsigned) TXC1)));    // waits until transmit complete bit is set
    PIND = 1u << (unsigned) XLAT;    // latches new Data
    PIND = 1u << (unsigned) XLAT;
    PORTC = (uint8_t) (~(0b001u << currentLayer));    // layer mosfet
    // blank goes low to start the next cycle, TLC will start to recount
    // make sure there is a 1µS delay before switching it again! (PCB board inverter)
    PIND = 1u << (unsigned) BLANK; // low (inverted)
    TCNT0 = 0;    // resets Counter

    shiftOutNr = 0;
    if (++currentLayer >= 3)
        currentLayer = 0;
    UDR1 = shiftOutInstruction[currentLayer][shiftOutNr];    // upload shiftOutBuffer[]
}

void updateDisplay(const uint8_t image[81]) {
    // converts 12 bit data into 8-bit data frames (MSPIM), MSB and channel first!
    for (unsigned int l = 0; l < 3; l++) {    // l for Layer
        // first 12bit data needs to be done separately, bc 27 is an odd number
        shiftOutInstruction[l][0] = (uint8_t) (lightness[image[26 + l * 27]] >> 8u);
        shiftOutInstruction[l][1] = (uint8_t) lightness[image[26 + l * 27]];
        for (unsigned int i = 0; i < 13; i++) {
            unsigned int sendIndex = (i * 3) + 2;    // s: send[]
            unsigned int dataIndex = (25 - (i * 2)) + l * 27;    // d: data[]
            shiftOutInstruction[l][sendIndex + 0] = (uint8_t) (lightness[image[dataIndex]] >> 4u);
            shiftOutInstruction[l][sendIndex + 1] = (uint8_t) ((lightness[image[dataIndex]] << 4u) +
                                                               (lightness[image[dataIndex - 1]] >> 8u));
            shiftOutInstruction[l][sendIndex + 2] = (uint8_t) lightness[image[dataIndex - 1]];
        }
    }
}
