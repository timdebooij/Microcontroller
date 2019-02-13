/*
 * CounterB2.c
 *
 * Created: 13-2-2019 14:51:18
 * Author : Tom Martens
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define BIT(x)(1 << (x))

void wait (int ms);

unsigned int i = 0; 

int main( void )
{
	TCCR2 = 0x07;
	unsigned char *c[7];
	DDRD &= ~BIT(7);
	DDRA = 0x00;
	init_4bits_mode();
	while (1)
	{
		if((PINA & 1) > 0)
		{
			i += 1;
			
			lcd_clear();
			itoa(i, c, 10);
			lcd_write_string(c);
		}
		wait(200);
	}
}

void wait (int ms)
{
	for (int i  = 0; i<ms; i++){
		_delay_ms(1);
	}
}
