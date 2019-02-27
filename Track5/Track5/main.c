/*
 * Track5.c
 *
 * Created: 27-2-2019 10:29:45
 * Author : timde
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000L

#define BIT(x) ( 1<<x )
#define DDR_SPI DDRB // spi Data direction register
#define PORT_SPI PORTB // spi Output register
#define SPI_SCK 1 // PB1: spi Pin System Clock
#define SPI_MOSI 2 // PB2: spi Pin MOSI
#define SPI_MISO 3 // PB3: spi Pin MISO
#define SPI_SS 0 // PB0: spi Pin Slave Select

char Help[4] = {0x0E,0x0D,0x0B, 0x0C};

// wait(): busy waiting for 'ms' millisecond - used library: util/delay.h
void wait(int ms)
{
	for (int i=0; i<ms; i++)
	_delay_ms(1);
}
void spi_masterInit(void)
{
	DDR_SPI = 0xff; // All pins output: MOSI, SCK, SS, SS_display
	DDR_SPI &= ~BIT(SPI_MISO); // except: MISO input
	PORT_SPI |= BIT(SPI_SS); // SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1); // or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64
	// bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
}
// Write a byte from master to slave
void spi_write( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
}
// Write a byte from master to slave and read a byte from slave - not used here
char spi_writeRead( unsigned char data )
{
	SPDR = data; // Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); // Wait for transmission complete
	data = SPDR; // New received data (eventually, MISO) in SPDR
	return data; // Return received byte
}
// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}
// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}
//Microcontrollers – TI2.3 - Opdrachten track 5 - versie 14-03-2016 Pagina 9 van 10
// Initialize the driver chip (type MAX 7219)
void displayDriverInit()
{
	spi_slaveSelect(0); // Select display chip (MAX7219)
	spi_write(0x09); // Register 09: Decode Mode
	spi_write(0xFF); // -> 1's = BCD mode for all digits
	spi_slaveDeSelect(0); // Deselect display chip
	spi_slaveSelect(0); // Select dispaly chip
	spi_write(0x0A); // Register 0A: Intensity
	
	//We changed the intensity to the max which is 0x0F
	spi_write(0x04); // -> Level 4 (in range [1..F])
	
	spi_slaveDeSelect(0); // Deselect display chip
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0B); // Register 0B: Scan-limit
				
	//We changed the display limit from 0x01 to 0x03 to enable all four, eight bit digits lED display drivers
	spi_write(0x03); // -> 1 = Display digits 0..1
	spi_slaveDeSelect(0); // Deselect display chip
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x01); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}
// Set display on ('normal operation')
void displayOn()
{
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x01); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}
// Set display off ('shut down')
void displayOff()
{
	spi_slaveSelect(0); // Select display chip
	spi_write(0x0C); // Register 0B: Shutdown register
	spi_write(0x00); // -> 1 = Normal operation
	spi_slaveDeSelect(0); // Deselect display chip
}

void spi_writeWord ( unsigned char adress, unsigned char data ){ // Write a word = address byte + data byte from master to slave
	spi_slaveSelect(0); // Select dispaly chip
	spi_write(adress); // WRITE ADDRESS
	spi_write(data); //  WRITE DATA
	spi_slaveDeSelect(0); // Deselect display chip
}

void writeLedDisplay( int value ){
	int amountDigits = floor (log10 (abs (value))) + 1;
	int second;
	int third;
	switch(amountDigits){
		case 1:
			if(value <0){
				spi_writeWord(2, 0x0A);
			}
			
			spi_writeWord(1, abs(value));
			break;
		case 2:
			if(value < 0){
				spi_writeWord(3, 0x0A);
			}
			
			spi_writeWord(1, ((abs(value))%10));
			spi_writeWord(2, (abs(value)/10));
			
			break;
		case 3:
			if(value < 0){
				spi_writeWord(4, 0x0A);
			}
			second = abs(value)%100;
			spi_writeWord(1, (second%10));
			spi_writeWord(2, (second/10));
			spi_writeWord(3, (abs(value)/100));
			break;
		case 4:
			if(value < 0){
				spi_writeWord(1, 0x0B);
			}
			else{
			third = value%1000;
			second = third%100;
			spi_writeWord(1, (second%10));
			spi_writeWord(2, (second/10));
			spi_writeWord(3, (third/100));
			spi_writeWord(4, (value/1000));
			}
			break;
		default:
			spi_writeWord(1, 0x0B);
			break;
	}
}

int main()
{
	DDRB=0x01; // Set PB0 pin as output for display select
	spi_masterInit(); // Initialize spi module
	displayDriverInit(); // Initialize display chip
	// clear display (all zero's)
	for (char i =1; i<=4; i++)
	{
		spi_slaveSelect(0); // Select display chip
		spi_write(i); // digit adress: (digit place)
		spi_write(0); // digit value: 0
		spi_slaveDeSelect(0); // Deselect display chip
	}
	wait(1000);
	// write 4-digit data
	//for (char i =1; i<=4; i++)
	//{
	//	spi_slaveSelect(0); // Select display chip
	//	spi_write(i); // digit adress: (digit place)
		
		//Changed the for loop to execute four times and change the number to 5-i (this means it writes 4 to display 1 and so on)
	//	spi_write(5-i); // digit value: i (= digit place)
	//	spi_slaveDeSelect(0); // Deselect display chip
	//	wait(1000);
	
	//}
	//Writes help to the displays
	//for(int i = 1; i<=4; i++){
	//	spi_writeWord(i, Help[i-1]);
	//}
	writeLedDisplay(-4);
	wait(1000);
	return (1);
}

