/*
 * spimaster.h
 *
 * Created: 27/07/2020 11:36:23 م
 *  Author: FGstore
 */ 


#ifndef SPIMASTER_H_
#define SPIMASTER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SCK 7
#define SPI_SS 6
#define Slave_EN (PORTD &=~(1<<SPI_SS))
#define Slave_DISABLE (PORTD |=(1<<SPI_SS))
void SPI_init();
unsigned char TXRX(unsigned char data);

//#define F_CPU 16000000UL
//#include <avr/io.h>
//#include <util/delay.h>

//#define SPI_MISO 6
//#define SPI_MOSI 5
//#define SPI_SCK 7
//#define SPI_SS 4
//#define Slave_EN (PORTC &=~(1<<SPI_SS))
//#define Slave_DISABLE (PORTC |=(1<<SPI_SS))

//unsigned char TXRX(unsigned char data);


//int main(void){
	
//}



void SPI_init(){
	DDRB|=(1<<SPI_MOSI)|(1<<SPI_SCK);
	DDRB &=~(1<<SPI_MISO);
	DDRC |=(1<<SPI_SS)|(1<<0);
	SPCR |= (1<<SPE) |(1<<MSTR)|(1<<SPR0);
}
unsigned char TXRX (unsigned char data){
	SPDR = data ;
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}

#endif /* SPIMASTER_H_ */