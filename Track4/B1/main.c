#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "display.h"

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
unsigned int reverseBits(unsigned int num);

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void init( void )
{
	ADMUX = 0b11100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11000110;		// ADC-enable, no interrupt, start, free running, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	unsigned char c[7];
	//FOR DISPLAY
	DDRD = 0xFF;
	init_4bits_mode();
	
	//FOR ADC
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output 
	DDRB = 0xFF;				// set PORTB for output
	init();					// initialize ADC

	while (1)
	{
		lcd_clear();
		//PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		
		
		lcd_write_string(itoa((ADCH << 1) /2, c, 10));
		wait(100);				// every 100 ms (busy waiting)
	}
}