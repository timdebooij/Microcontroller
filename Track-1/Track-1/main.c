/*
 * Track-1.c
 *
 * Created: 30/01/2019 10:20:55
 * Author : Patrick, Simon, Tom
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <stdio.h>
#include "util.h"

int main(void)
{
	//Set pins from port D to output. With 1, can be input with 0.
    DDRD = 0b11111111;
	
	while(1){
		PORTD = 0xAA;
		wait(1000);
		PORTD = 0x55;
		wait(1000);
	}
	
	return 1;
}

