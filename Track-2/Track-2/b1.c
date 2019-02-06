/*
 * b1.c
 *
 * Created: 6-2-2019 11:04:09
 *  Author: timde
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "util.h"

/******************************************************************/
ISR( INT0_vect )
/* 
short:			ISR INT0
inputs:			
outputs:	
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
    PORTD |= (1<<5);		
}

/******************************************************************/
//ISR( INT1_vect )
/* 
short:			ISR INT1
inputs:			
outputs:	
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
//{
//    PORTD &= ~(1<<5);		
//}


void runb1() {
		// Init I/O
		DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input

		// Init Interrupt hardware
		EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
		EIMSK |= 0x03;			// Enable INT1 & INT0
		
		// Enable global interrupt system
		//SREG = 0x80;			// Of direct via SREG of via wrapper
		sei();

		while (1)
		{
			PORTD ^= (1<<7);	// Toggle PORTD.7
			wait( 500 );
		}

}
