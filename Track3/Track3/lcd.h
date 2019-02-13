/*
 * lcd.h
 *
 * Created: 13/02/2019 09:48:42
 *  Author: Patrick
 */ 

void lcd_strobe_lcd_e(void);
void lcd_clear();
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_setCursor(int position);
void lcd_writeChar( unsigned char dat);
void lcd_writeLine1 ( char text1[] );
void lcd_writeLine2 ( char text1[] );
