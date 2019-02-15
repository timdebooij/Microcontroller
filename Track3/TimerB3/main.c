/*
 * TimerB3.c
 *
 * Author : Simon, Patrick, Tim en Tom
 */ 

#include <avr/io.h>


#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

int counter = 0;
int ms_counter = 0;
int mses[] = {25, 15};
ISR(TIMER2_COMP_vect){
	if((++counter) > mses[ms_counter]){
		PORTD ^= 1;
		TCNT2 = 0;
		ms_counter = (ms_counter+1)%2;
		counter = 0;
	}
}


void main(){
	DDRD = 0xff;

	TCNT2 = 0;
	OCR2 = 0x05;
	TCCR2 = (1 << WGM21) | (1 << CS20)| (1 << CS22);
	TIMSK = (1 << OCIE2);
	sei();

	while(1){

	}
}