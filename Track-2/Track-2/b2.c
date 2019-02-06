/*
 * b2.c
 *
 * Created: 6-2-2019 11:11:42
 *  Author: timde
 */ 
#define F_CPU 8000000L

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "util.h"

int position = 3;

void setLightNext(){
	
	
}

/*
ISR( INT1_vect ){
	position+=1;
	if(position == 8){
		position = 3;
	}
	int oldPos = position-1;
	if(oldPos == -1){
		oldPos = 7;
	}
	PORTD &= ~(1<<oldPos);
	wait(200);
	PORTD |= (1<<position);
}

ISR( INT2_vect){
	position += 1;
	if(position == 8){
		position = 3;
	}
	int oldPos = position-1;
	if(oldPos == 2){
		oldPos = 7;
	}
	PORTD &= ~(1<<oldPos);

	PORTD |= (1<<position);
} */



void runb2(){
	DDRD = 0b11111000;
	EIMSK |= 0x07;
	sei();
	while(1){
		
	}
}
