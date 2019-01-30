#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void s1(void);
void s2(void);
void s3(void);
void end(void);
void start(void);


typedef enum { D7, D5 } ENUM_EVENTS;
typedef enum { START, STATE_1, STATE_2, STATE_3, END } ENUM_STATES;


typedef struct {
	void (*finit)(void);
	void (*fbody)(void);
	void (*fexit)(void);
	ENUM_STATES nextState;
} STATE_TRANSITION_STRUCT;

STATE_TRANSITION_STRUCT fsm[5][3] = {
	{ {s1,   NULL,  NULL, START}, 	{NULL, s1, NULL, STATE_1},		{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START},	{NULL, NULL, NULL, STATE_1},	{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START}, 	{NULL, s1, NULL, STATE_1}, 		{NULL, s3, NULL, STATE_3} },
	{ {NULL, NULL,  NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} },
	{ {NULL, start, NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} }
};


ENUM_STATES state = START;


void handleEvent(ENUM_EVENTS event)
{
	// Call EXIT function old state
	if( fsm[state][event].fexit != NULL) {
		fsm[state][event].fexit() ;
	}
	
	// Set new state, -1 means
	state = fsm[state][event].nextState;

	// Call INIT function
	if( fsm[state][event].finit != NULL) {
		fsm[state][event].finit() ;
	}

	// Call BODY function
	if( fsm[state][event].fbody != NULL) {
		fsm[state][event].fbody() ;
	}
}

//
// State S1
//
void s1(void){
	PORTD = 0x1;
	wait(500);
}

//
// State S2
//
void s2(void){
	PORTD = 0x2;
	wait(500);
}

// State S3
void s3(void){
	PORTD = 0x4;
	wait(500);
}

void start(void){
	PORTD = 0xFF;
	wait(500);
	PORTD = 0x00;
}

void end(void){
	PORTD = 0xFF;
	wait(500);
	PORTD = 0x00;
}


int main( void )
{
	
	DDRD = 0b00001111;	
	while (1)
	{
			handleEvent(D7);
			handleEvent(D5);
	}

	return 1;
}
