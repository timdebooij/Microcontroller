/*
* task.h
*
* Created: 30/01/2019 12:38:00
*  Author: Patrick, Simon, Tom
*/

#ifndef TASK_H_
#define TASK_H_
#include "util.h"

void b2() {
	DDRD = 0b11111111;
	
	while(1){
		PORTD = 0x80;
		wait(500);
		PORTD = 0x40;
		wait(500);
	}
}

void b3() {
	DDRC = 0b00000000;
	DDRD = 0b11111111;
		
	while(1) {
		if(PINC & 1)
		{
			PORTD = 0x80;
			wait(250);
			PORTD = 0x00;
			wait(250);
		} else {
			PORTD = 0x00;
		}
	}
}

void b4() {
	DDRD = 0b11111111;
	
	while(1){
		for(int index = 0x01; index < 0x80; index <<= 1) {
			PORTD = index;
			wait(50);
		}
		
		for(int index = 0x80; index > 0x01; index >>= 1) {
			PORTD = index;
			wait(50);
		}
	}
}

void b5() {
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	
	DDRD = 0b11111111;
	DDRE = 0b11111111;
	DDRF = 0b11111111;
	
	DDRG = 0b11111111;
	
	int index = 0;
	while(1) {
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
		if(index < 7) {
			index++;
			} else {
			index = 0;
		}
	}	
}

void b6() {
	DDRC = 0b00000000;
	DDRD = 0b11111111;
	
	int button = 0;
	
	while(1) {
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


void b7a() {
	
}

#endif /* TASK_H_ */