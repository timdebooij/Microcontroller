/*
* task.h
*
* Created: 30/01/2019 12:38:00
*  Author: Patrick, Simon, Tom
*/

#ifndef TASK_H_
#define TASK_H_

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
			printf("triggered");
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



#endif /* TASK_H_ */