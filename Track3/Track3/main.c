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
{
	// Initializing I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Initializing the display
	init_4bits_mode();

	// Sending sample String to display to test it
	lcd_write_string("Microcontrollers");
	// Put the cursor 40 position's back
	setCursor(-40);

	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}

