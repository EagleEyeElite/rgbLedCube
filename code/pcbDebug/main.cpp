/*
 * DebugCircuit.cpp
 *
 * Created: 28.05.2018 20:22:08
 * Author : Conrad
 *
 * Fuses: Low: 0xFF, High: 0xD9, Extended: 0xFC
 */ 
#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>


#define BLANK 0    // PD0
#define VPRG 1    // PD1
#define IR_Rec 2// PD2
#define SIN 3    // PD3	// set
#define SCLK 4    // PD4	// set
#define GSCLK 5    // PD5	// OC1A
#define XLAT 6    // PD6
#define LED 7   // PD7

#define SW        //PB2	// use pull UP Resistor
// PC0-PC2 mosfet-Outputs (Inverted)


void inbuilt_LED();
void setUpLayerMosfet();
void WriteTlc(uint16_t Data[]);
void WriteTlcByte(uint8_t Data[]);
void updateMosfet();

void setupTLC();
void updateTLC();
volatile uint16_t Data[27] = {0xFFF, 0x000, 0xFFF, 0x000, 0xFFF, 0x000, 0x000, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF};

volatile uint8_t send[41];
volatile uint8_t num = 0;
//volatile uint8_t sendLength = 41;	//(27*12 bits -> 40.5 * 8bits)
volatile uint8_t done = 1;
volatile uint8_t newData = 0;
/*
ISR(USART1_UDRE_vect) {	//clocks in Data
	UDR1 = send[num++];
	if(num >= 41)	//(27*12 bits -> 40.5 * 8bits)
		UCSR1B &= ~(1 << UDRIE1);	//disable (own) Interrupt!
}

ISR(USART1_TX_vect) {	//latches Data + set num ... to 0
	PORTD |= 1<<XLAT;	//latch data in
	PORTD &= ~(1<<XLAT);
	done = 1;
	num = 0;
}
*/
void setupTLC() {
	DDRD |= (1<<BLANK) | (1<<VPRG) | (1<<SIN) | (1<<SCLK) | (1<<GSCLK) | (1<<XLAT);	//Define as output
	
	//set DC!	//add: put 0x00 into unused pins, to Protect them
	PORTD  &= ~(1<<BLANK);	//high (inverted)
	PORTD |= (1<<VPRG);	//DC Data Input Mode
	PORTD |= (1<<SIN);
	PORTD  &= ~(1<<SCLK);
	for(int c=0; c<27; c++) {	//c = Channel
		for(int b=0; b<6; b++) {	//b = bit
			PIND = (1<<SCLK);
			PIND = (1<<SCLK);	//low
		}
	}
	PORTD |= (1<<XLAT);
	PORTD  &= ~(1<<XLAT);
	PORTD &= ~(1<<VPRG);	//GS Data Input Mode
    /*
    //Turn on MSPIM Mode: starts USART as SPI: MSPI: SPI-mode 0, MSB, baudrate: 0
    cli();
    UBRR1 = 0;
    DDRD |= (1<<SCLK);
    UCSR1C = (1<<UMSEL10) | (1<<UMSEL11);
    UCSR1B |= (1<<TXEN1) | (1<<TXCIE1);	//TX enable + TX complete interrupt enable
    UBRR1 = 0;

    sei();
    */
}

void updateTLC() {
	//Generate Byte List to send (from Data[])
	newData = 1;
	//Converts 12 bit Data into 8-bit Data Frames (MSPIM), MSB and Channel first!
	send[0] = Data[26] >> 8;	//27 is odd, first 12bit Data needs to be done separately
	send[1] = Data[26];
	for(int i=0; i<13; i++) {
		int tempS = (i*3)+2;	//S: Send[]
		int tempD = 25-(i*2);	//D: Data[]
		send[tempS+0] = Data[tempD] >> 4;
		send[tempS+1] = (Data[tempD] << 4) + (Data[tempD-1] >> 8);
		send[tempS+2] = Data[tempD-1];
	}

	//Send Data - older version (new: MSPIM)
	PORTD &= ~(1<<VPRG);	//GS Data Input Mode
	for(int s=0; s<41; s++) {	//s = send[]
		for(int b=0; b<8; b++) {	//b = bit
			if((send[s] >> (7-b)) & 1)	//Data[27-c]
				PORTD |= (1<<SIN);
			else
				PORTD &= ~(1<<SIN);
			
			PORTD |= (1<<SCLK);
			PORTD  &= ~(1<<SCLK);	//low
		}
	}

/*
	sei();		//Interrupt must be set or this upload cant work (will be caught in an endless loop) -> add if statement into while loop!
	done = 0;
	num = 0;
	UCSR1B |= (1 << UDRIE1);	//upload send[]!!! -> Interrupt is enabled
	
	while ( done == 0);  //wait for transmit complete
*/
	
	PORTD |= (1<<XLAT);
	PORTD  &= ~(1<<XLAT);	//low
}
	
int main(void)
{	
	inbuilt_LED();
	setUpLayerMosfet();
	setupTLC();
	updateTLC();
	uint16_t brightness = 0;
	
	while (1)
	{
		PORTD  &= ~(1<<GSCLK);	//low
		for(uint16_t i=0; i<=0xFFE; i++) {
			PIND = (1<<GSCLK);
			PIND = (1<<GSCLK);
		}
		PORTD  &= ~(1<<BLANK);	//high (inverted)
		_delay_us(1);
		PORTD |= (1<<BLANK);
		_delay_us(1);
		
		brightness += 0x1;
		if (brightness >= 0x9FF) {
			brightness = 0;
		}
		//Data[0] = brightness;
		//Data[4] = brightness;
		//Data[8] = brightness;
		for(int i=0; i<= 26; i++) {
			Data[i] = brightness;
			//updateMosfets();
		}
		updateTLC();
		
	}
}


void setUpLayerMosfet() {
    DDRC = 0b00000111;    // mosfet -Output
    PORTC = 0b00000101;    // mosfet -high (inverted)
}

volatile int Layer = 0;
void updateMosfet() {
	Layer++;
	if (Layer == 3)
		Layer = 0;
	PORTC = ~(0b100 >> Layer);
}

void inbuilt_LED() {
	DDRD |= (1<<LED);	//led -Output
	PORTD |= (1<<LED);	//led -High
	DDRB = 0b00000000;	//switch, input
	PORTB = 0b00000100;	//switch, tristate/pull up
}
