/*
 * Track4.c
 *
 * Created: 20-2-2019 10:18:26
 * Author : timde
 */ 



#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void init(){
	ADMUX = 0b01100001; //C: De eerste 2 bits bepalen de voltage reference selection, 01 zorgt voor "AVCC with external capacitor at AREF pin"
						//D: De 5e bit bepaald de presentatie van de adc conversie. een 1 zorgt voor "left adjusted result"
						//E: admux adc1 aan, pin 60 (laatste 5 bits bepalen dit)
	
	ADCSRA = 0b11100110;//B: laatste 3 bits bepalen dat de prescaler op 64 staat, namelijk 110
						//F: Bit 5 zorgt ervoor dat de freerunning mode aangezet kan worden, daarom staat hij bij ons op 1, dit zorgt ervoor dat er continu samples aanleverd aan de data register en dit update
						//G: Bit 7 zorgt ervoor dat de adc aangezet wordt, daarom staat deze op 1
						//H: Bit 6 zorgt ervoor dat de adc gaat runnen. Bij freerunning mode zorgt deze ervoor dat de eerste conversie wordt gestart
}

void initB3(){
	ADMUX = 0b01100011;
	//channel is veranderd van 1 naar 3
	ADCSRA = 0b10000110;
	//freerunning mode is uit
	//start conversion is uit
}

int main(void)
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	DDRB = 0xFF;				// set PORTB for output
	DDRD = 111110000;
	EICRA = 00000011;
	sei();
	initB3();					// initialize ADC

    /* Replace with your application code */
    while (1) 
    {
		
		ADCSRA = 0b11000110;
		//PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		wait(1000);				// every 100 ms (busy waiting)
		
    }
}

