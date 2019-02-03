/*
 * util.c
 *
 * Created: 03/02/2019 16:33:22
 *  Author: Patrick, Simon, Tom, Tim
 */ 
#define F_CPU 8000000L
#include <util/delay.h>


// Delivered from school, this method will make sure the device will wait a certain ms, the amount of waiting depends on the parameter you fill in
void wait (int ms)
 {
	 for (int i  = 0; i<ms; i++){
		 _delay_ms(1);
	 }
 }
