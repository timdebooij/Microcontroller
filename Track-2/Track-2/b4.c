/*
 * b4.c
 *
 * Created: 06/02/2019 15:16:51
 *  Author: Patrick
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "b4.h"
#include "util.h"

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;


PATTERN_STRUCT pattern[] = {
	{0x80, 1}, {0x00, 1},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0b00010000, 150},
	{0b00001000, 150}, {0b00000100, 150}, {0x40, 150}, {0b00100000,150},
	{0xFF, 0}
};

void runb4() {
	DDRD = 0b11111111;					// PORTD all output
	
	while (1==1)
	{
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}
}