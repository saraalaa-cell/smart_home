/*
 * uart.h
 *
 * Created: 27/07/2020 11:31:29 م
 *  Author: FGstore
 */ 


#ifndef UART_H_
#define UART_H_
//#include "uart.c"
//void Uart_Init( long USART_BAUDRATE);
//void Uart_Txc( char data);
//char  Uart_Rxc( );
//void Uart_string(char* string);

#include <avr/io.h>
#define F_CPU 16000000UL
#define Baud_Prescal (((F_CPU/(16UL*USART_BAUDRATE)))-1)
void Uart_Init( long USART_BAUDRATE);
void Uart_Txc( char data);
char  Uart_Rxc( );
void Uart_string(char* string);







void Uart_Init( long USART_BAUDRATE){
	UCSRB |=(1<<RXEN)|(1<<TXEN);
	UCSRC |=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL = Baud_Prescal;
	
	
}
void Uart_Txc( char data){
	while(!(UCSRA &(1<<UDRE)));
	UDR = data;
}
char  Uart_Rxc( ){
	while((UCSRA &(1<<RXC))==0);
	return UDR;
}
void Uart_string(char* string){
	char i;
	while(string[i] !=0){
		Uart_Txc( string[i]);
		i++;
	}
}


#endif /* UART_H_ */