/*
 * util.h
 *
 * Created: 6-2-2019 11:07:03
 *  Author: timde
 */ 


/******************************************************************/
void wait( int ms );
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
