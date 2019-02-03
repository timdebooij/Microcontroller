/*
 * task.c
 *
 * Created: 03/02/2019 16:29:57
 *  Author: Patrick, Tom, Tim, Simon
 */ 
#define F_CPU 8000000L
#include "util.h"
#include <avr/io.h>

// This Function will make the light flicker between the first led and the second led
void b2() {
	// We turn all of the LED's on output on Row D, because we need to turn on the LED's and not retrieve information.
	DDRD = 0b11111111;
	
	while(1){
		// Turn the first led on, 0x80 -> 0b1000 0000. The 1 is the one you turn on, 0 means it's turned off
		PORTD = 0x80;
		// Waiting 500 ms 
		wait(500);
		// Same as before but now you turn on the second LED, 0x40 -> 0b0100 0000
		PORTD = 0x40;
		wait(500);
	}
}

/// This function will make 
void b3() {
	
	// We turned all of the buttons on row C to input, because unlike the LED's we need to information when we press a button.
	DDRC = 0b00000000;
	// We turn all of the LED's on output on row D, because we need to turn on the LED's and not retrieve information.
	DDRD = 0b11111111;
		
	while(1) {
		// Checking if the button Number is 1 if not turn the LED's on Row D off
		if(PINC & 1)
		{
			/* If button number is 1 then make the light flicker by turning it off and on again every 250 ms
			 * 0x80 > 0b1000 0000
			 */
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
			wait(250);
		} else {
			PORTD = 0x00;
		}
	}
}


// This function will make the LED's row animate like a walking light
void b4() {
	// We turn all of the LED's on output on row D, because we need to turn on the LED's and not retrieve information.
	DDRD = 0b11111111;
	
	while(1){
		// This will increment every light and turn it on 
		for(int index = 0x01; index < 0x80; index <<= 1) {
			PORTD = index;
			wait(50);
		}
		// This will decrement every light and turn it on 
		for(int index = 0x80; index > 0x01; index >>= 1) {
			PORTD = index;
			wait(50);
		}
	}
}

// Same as B4 but then with multiple LED Rows, Also the task was to make a less maintainable code
void b5() {
	// We turn all of the LED's on output on row ABCDEFG, because we need to turn on the LED's and not retrieve information.
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	
	DDRD = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	
	DDRG = 0b11111111;
	
	// keep indexing for every row
	int index = 0;
	while(1) {
		// Depending on the index of the row turn on that row and 50 ms, 0xFF -> 0b1111 1111
		switch(index)
		{
			case 0:
				PORTA = 0xFF;
				wait(50);
				
				break;
			case 1:
				PORTB = 0xFF;
				wait(50);
				break;
			case 2:
				PORTC = 0xFF;
				wait(50);
				break;
			case 3:
				PORTD = 0xFF;
				wait(50);
				break;
			case 4:
				PORTE = 0xFF;
				wait(50);
				break;
			case 5:
				PORTF = 0xFF;
				wait(50);
				break;
			case 6:
				// Turn on the last row and then turn off all of the rows
				PORTG = 0xFF;
				wait(50);
				PORTA = 0x00;
				wait(50);
				PORTB = 0x00;
				wait(50);
				PORTC = 0x00;
				wait(50);
				PORTD = 0x00;
				wait(50);
				PORTE = 0x00;
				wait(50);
				PORTF = 0x00;
				wait(50);
				PORTG= 0x00;
				wait(50);
				break;
		}
		// Make sure index is not greater then 7 because we only have 7 rows, 
		// if it is lower then 7 then put it back on 0 and the switch case starts over again
		if(index < 7) {
			index++;
		} else {
			index = 0;
		}
	}	
}

// Task that makes works with coding states 
void b6() {
	
	// We turned all of the buttons on row C to input, because unlike the LED's we need to information when we press a button.
	DDRC = 0b00000000;
	// We turn all of the LED's on output on row D, because we need to turn on the LED's and not retrieve information.
	DDRD = 0b11111111;
	
	// index for button
	int button = 0;
	
	while(1) {
		// Checking if the button Number is 1.
		if(PINC & 1)
		{
			
			switch(button){
				case 0:
				button = 1;
				break;
				
				case 1:
				button = 0;
				break;
				
			}	
		}
		
		switch(button){
			case 0:
			PORTD = 0x80;
			wait(1000);
			PORTD = 0x00;
			wait(1000);
			break;
			
			case 1:
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
			wait(250);
			break;
		}
	}
}