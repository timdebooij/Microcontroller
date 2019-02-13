#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2


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
	lcd_clear();
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

void lcd_write_string(char *str)
{
	for(;*str; str++){
		lcd_write_data(*str);
	}
}


void lcd_write_data(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_write_command(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_setCursor(int position) {
	
}