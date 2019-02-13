#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_write_command(unsigned char dat);
void lcd_writeChar( unsigned char dat);


void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void lcd_clear(void) {
	lcd_write_command(0x01);
}
void init_4bits_mode(void)
{
	//lcd_clear();
	// return home
	lcd_write_command( 0x02 );
	// mode: 4 bits interface data, 2 lines, 5x8 dots
	lcd_write_command( 0x28 );
	// display: on, cursor off, blinking off
	lcd_write_command( 0x0C );
	// entry mode: cursor to right, no shift 
	lcd_write_command( 0x06 );
	// RAM adress: 0, first position, line 1 
	lcd_write_command( 0x80 );

}


void lcd_writeLine1 ( char text1[] )
{
	lcd_write_command(0x80);
	for (int i=0; i<16; i++) 
	{
			lcd_writeChar( text1[i] );
	}
}

void lcd_writeLine2 ( char text2[] )
{
	lcd_write_command(0xC0);
	for (int i=0; i<16; i++)
	{
		lcd_writeChar( text2[i] );
	}
}

void lcd_writeChar( unsigned char dat)
{
	PORTC = dat& 0xF0;
	PORTC = PORTC | 0x0C;
	_delay_ms(1);
	PORTC = 0x04;
	PORTC = (dat& 0x0F) << 4;
	PORTC = PORTC | 0x0C;
	_delay_ms(1);
	PORTC = 0x00;
}

void lcd_write_command(unsigned char dat)
{
	PORTC = dat & 0xF0;
	PORTC = PORTC | 0x08;
	_delay_ms(1);
	PORTC = 0x04;
	PORTC = (dat& 0x0F) << 4;
	PORTC = PORTC | 0x08;
	_delay_ms(1);
	PORTC = 0x00;
}
