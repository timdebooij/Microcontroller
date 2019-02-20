#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "display.h"

// Pre made Wait function
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			
	}
}

void init( void )
{
	ADMUX = 0b11100001;			// Same as B1 but now turned off B3
	ADCSRA = 0b11000110;		
}


// Main program: ADC at PF1
int main( void )
{
	unsigned char c[7];
	
	DDRD = 0xFF;
	// Same as last weeks
	init_4bits_mode();
	
	//FOR ADC
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output 
	DDRB = 0xFF;				// set PORTB for output
	init();					// initialize ADC

	while (1)
	{
		// Clearing screen
		lcd_clear();
		
		PORTA = ADCH;
		
		// Writing to screen, itoa for setting bit to char
		lcd_write_string(itoa((ADCH << 1) /2, c, 10));
		wait(100);				// every 100 ms (busy waiting)
	}
}