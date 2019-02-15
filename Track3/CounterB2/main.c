/*
 * CounterB2.c
 *
 * Created: 13-2-2019 14:51:18
 * Author : Tim, Tom, Patrick, Simon
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

#define BIT(x)(1 << (x))

void wait (int ms);

int main( void )
{
	unsigned char c[7];
	DDRD &= ~BIT(7);
	TCCR2 = 0b00000111;
	DDRB = 0xFF;
	PORTB = TCNT2;
	init_4bits_mode();
	int currrentValue = TCNT2;
	
	while (1)
	{
		if(currrentValue != TCNT2)
		{
			currrentValue = TCNT2;
			sprintf(c,"%i",TCNT2);
			lcd_clear();
			lcd_write_string(c);
			
		}
	}
	
}

void wait (int ms)
{
	for (int i  = 0; i<ms; i++){
		_delay_ms(1);
	}
}
