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
#include <avr/iom128a.h>

#include "util.h"

//The position determines which light is activated on PORTD
int position = 3;

/*
This function turns off the current activated light and activates the next one 
*/
void setLight(){
	position+=1;
	if(position == 8){
		position = 3;
	}
	int oldPos = position-1;
	if(oldPos == 2){
		oldPos = 7;
	}
	PORTD &= ~(1<<oldPos);
	wait(100);
	PORTD |= (1<<position);
}

/*
ISR(INT0_vect){
	
}

//Is called when INT1 is pressed
ISR( INT1_vect ){
	setLight();
}

//Is called when INT2 is pressed
ISR( INT2_vect ){
	setLight();
}
*/


/*
In this function the last five bits of Direction D are set to output and the INT0, INT1 and INT2 are activated.
*/
void runb2(){
	DDRD = 0b11111000;
	EIMSK |= 0x07;
	sei();
	while(1){
		
	}
}
