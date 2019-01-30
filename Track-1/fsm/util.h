/*
 * util.h
 *
 * Created: 1/30/2019 11:14:54 AM
 *  Author: Simon, Tom, Patrick
 */ 


#ifndef UTIL_H_
#define UTIL_H_
#include <util/delay.h>

void wait (int ms) {
	for (int i  = 0; i<ms; i++){
		_delay_ms(1);
	}
}


#endif /* UTIL_H_ */