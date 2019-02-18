/*
 * lcd.c
 *
 * Created: 13/02/2019 09:48:42
 *  Author: Patrick, Tim, Simon, Tom
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2


void lcd_strobe_lcd_e(void)
{
	// Set E on high
	PORTC |= (1<<LCD_E);	
	_delay_ms(1);	
	// Set E low		
	PORTC &= ~(1<<LCD_E);  	
	_delay_ms(1);			
}

// initialize LCD display to 4 bits mode, stroping display to make the changes
void init_4bits_mode(void)
{
	// Set PORTC to output and set everything on low
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Display on & off control
	PORTC = 0x00;   
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Turn on entry mode
	PORTC = 0x00;   
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

}

// This function will write String to the display;
void lcd_write_string(char *str)
{
	// Looping through every character in the string to display the whole word
	for(;*str; str++){
		lcd_write_data(*str);
	}
}


// Writing Byte to display
void lcd_write_data(unsigned char byte)
{
	//A NIBBLE EXISTS OUT OF HALF A BYTE SO ONE BYTE IS 2 NIBBLES!!! SOURCE: https://nl.wikipedia.org/wiki/Nibble
	// Sending the first Nibble of a byte
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Sending second Nibble of a byte
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

// Sending command to the display
void lcd_write_command(unsigned char byte)
{
	//A NIBBLE EXISTS OUT OF HALF A BYTE SO ONE BYTE IS 2 NIBBLES!!! SOURCE: https://nl.wikipedia.org/wiki/Nibble
	// Sending the first Nibble of a byte
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Sending second Nibble of a byte
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

// This will set cursor of the display on a certain position
void setCursor(int pos)
{
	// Set cursor forward
	if(pos > 0)
	{
		for(int i = 0; i < pos; i++)
		{
			lcd_write_command(0x1C);
			_delay_ms(1000);
		}
	}
	// Puts cursor further back depending on the value pos
	else if(pos < 0)
	{
		for(int i = 0; i > pos; i--)
		{
			lcd_write_command(0x18);
			_delay_ms(1000);
		}
		
	}
}
