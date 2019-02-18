/*
 * lcd.h
 *
 * Created: 13/02/2019 09:48:42
 *  Author: Patrick, Tim, Simon, Tom
 */ 

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void setCursor(int pos);
