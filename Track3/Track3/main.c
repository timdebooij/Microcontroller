/*
 * Track3.c
 *
 * Created: 13/02/2019 09:45:21
 * Author : Patrick, Simon, Tim, Tom
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"



int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	// Write sample string
	lcd_write_string("Microcontrollers");
	setCursor(-40);

	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}

