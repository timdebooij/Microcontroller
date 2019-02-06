/*
* b3.c
*
* Created: 06/02/2019 12:17:50
*  Author: Patrick, Simon, Tim, Tom
*/
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "util.h"
#include "b3.h"

volatile int count = 5;
//Array of binary number to make show the items on display
const unsigned int num[16] =
{
	0b0111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111111, // B
	0b00111001, // C
	0b00111111, // D
	0b01111001, // E
	0b01110001 // F
};

// Function  to turn on the 7 segment display
void displayNum(int index) {
	// Check if index is higher/equal then zero and lower/equal to 15
	if(index >= 0 && index <= 15) {
		PORTA = num[index];
	}
	else {
		// Set segment to E
		PORTA = num[14];
	}
}

ISR(INT1_vect) {
	// increment before displaying;
	count += 1;
	displayNum(count);
}

ISR(INT2_vect) {
	// decrement
	count -= 1;
	displayNum(count);
	
}

void runb3() {
	// put all of he leds on output.
	DDRA = 0b11111111;
	//Put all of the button on output so they wont scan for input.
	DDRD = 0b11111001;
	// set register
	EICRA |= 0b00111100;
	// Set mask
	EIMSK |= 0b00000110;
	
	sei();
	while(1) {
	}
}