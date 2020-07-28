/*
 * smart_home_slave.c
 *
 * Created: 26/07/2020 05:02:12 م
 * Author : FGstore
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SCK 7
#define SPI_SS 6
#define Slave_EN (PORTD &=~(1<<SPI_SS))
#define Slave_DISABLE (PORTD |=(1<<SPI_SS))
void SPI_init();
unsigned char TRANSMITRECIVE(unsigned char data);
void steppermotor(unsigned char mode);



int main (void){
	 Slave_EN;
	SPI_init();
	DDRC |=(1<<0)|(1<<3)|(1<<4)|(1<<5)|(1<<6);
	DDRD |=(1<<5)|(1<<6);
	PORTD|=(1<<5)|(1<<6);
	
	char noentered =0;
	while(1){
		
		if( TRANSMITRECIVE('5')=='1'){ 
			PORTC |=(1<<0); 
			Slave_DISABLE;	
		}
		if(TRANSMITRECIVE('1')=='2'){
			PORTC &=~(1<<0);
			Slave_DISABLE;	 
			
		}	
		if (TRANSMITRECIVE('2')=='3')
		{
			PORTC =0X00;
			steppermotor(2);
			_delay_ms(1000);
			PORTC =0X00;
			Slave_DISABLE;
		}
		if (TRANSMITRECIVE('3')=='4')
		{
			PORTC =0X00;
			steppermotor(4);
			_delay_ms(1000);
			PORTC =0X00;
			Slave_DISABLE;
		}
		
	}
}
void steppermotor(unsigned char mode){
	switch (mode)
	{
		case 1:
		PORTC|=(1<<PC5)|(1<<PC6);
		PORTC &=~(1<<PC3)|(1<<PC4);
		break;
		case 2:
		PORTC|=(1<<PC5)|(1<<PC4);
		PORTC &=~(1<<PC3)|(1<<PC6);
		break;
		case 3:
		PORTC|=(1<<PC3)|(1<<PC4);
		PORTC &=~(1<<PC5)|(1<<PC6);
		break;
		case 4:
		PORTC|=(1<<PC3)|(1<<PC6);
		PORTC &=~(1<<PC5)|(1<<PC4);
		break;
	}
	

}
void SPI_init(){
	DDRB|=(1<<SPI_MISO);
	DDRB &=~(1<<SPI_MOSI)|(1<<SPI_SS);
	SPCR |= (1<<SPE) ;
}
unsigned char  TRANSMITRECIVE (unsigned char data){
	SPDR = data ;
	while (!(SPSR & (1<<SPIF)));
	return SPDR;

}
