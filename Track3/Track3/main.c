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


int main()
{
	DDRD = 0xFF;
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	char str[] = "Look at me";
	// Write sample string
	lcd_writeLine1(str);
	lcd_writeLine2(str);
	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}
	return 0;
}

