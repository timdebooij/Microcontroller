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

int counter = 0;
int ms_counter = 0;
int mses[] = {25, 15};
	
// Set de global iterupt wanneer de compare value getriggered wordt
ISR(TIMER2_COMP_vect){
	
	// Deze if statement zorgt ervoor dat het lampje op port D eerst 15ms aanstaat en dan 25ms uit.
	if((++counter) > mses[ms_counter]){
		PORTD ^= 1;
		TCNT2 = 0;
		ms_counter = (ms_counter+1)%2;
		counter = 0;
	}
}


int main(){
	DDRD = 0xff; //set LED as output

	TCNT2 = 0; // Setup Timer via PD7, rising edge
	OCR2 = 0x05; // Set CTC compare value
	TCCR2 = (1 << WGM21) | (1 << CS20)| (1 << CS22); // Setup timer 
	TIMSK = (1 << OCIE2); // Enable overflow interrupt
	sei(); // Enable global interrupts

	while(1){

	}
}