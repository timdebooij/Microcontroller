/*
 * util.c
 *
 * Created: 6-2-2019 11:06:24
 *  Author: timde
 */ 
#define F_CPU 8000000L
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
