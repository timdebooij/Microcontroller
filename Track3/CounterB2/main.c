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

int main( void )
{
	//een char array voor het opslaan (en tonen) van de cijfers op het LCD schermpje
	unsigned char c[7];
	//PD7 op input
	DDRD &= ~BIT(7);
	//Tellen via PD7, rising edge (voor accuraatheid)
	TCCR2 = 0b00000111;
	//PORTB is een output
	DDRB = 0xFF;
	//Counter toewijzen, toont waarde van TCCR2
	PORTB = TCNT2;
	//Het initaliseren van het LCD scherm
	init_4bits_mode();
	//Bijhouden hoevaak er op het knopje gedrukt is, TCNT2 bevat deze waarde, TCNT2 = 8-bit timer 
	int currrentValue = TCNT2;
	
	while (1)
	{
		//Controleren of er op het knopje gedrukt is (doe anders niks)
		if(currrentValue != TCNT2)
		{
			//Waarde van currentvalue weer aanpassen aan hoevaak er op het knopje is gedrukt
			currrentValue = TCNT2;
			//de waarde van TCNT2 opslaan in c
			sprintf(c,"%i",TCNT2);
			//Clearen voordat we gaan schrijven op het LCD schermpje
			lcd_clear();
			//Schrijf de string op het LCD schermpje
			lcd_write_string(c);
			
		}
	}
	
}
