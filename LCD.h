/*
 * LCD.h
 *
 * Created: 28/07/2020 11:43:35 ص
 *  Author: FGstore
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_cpu 16000000UL
#include <util/delay.h>

#include "DIO_CFG.h"


#define LCD_data_port DIO_PORTA
#define LCD_dir_port DDRA_Reg

#define LCD_control_port  DIO_PORTB
#define LCD_control_dir  DDRB_Reg



#define LCD_RS DIO_ChannelB1
#define LCD_RW	DIO_ChannelB2
#define LCD_E DIO_ChannelB3

void LCD_init(void);
void LCD_command(uint8 cmnd);
void LCD_data(uint8 data);
void LCD_String(char* string);
void LCD_charpos(uint8 line,uint8 pos,uint8 data);
void LCD_stringpos(uint8 line,uint8 pos,char* string);
void LCD_SPchar(uint8 loc,uint8 *msg);

void LCD_init(void){
	DIO_Init();
	DIO_WriteChannel(LCD_RW,STD_Low);
	_delay_ms(20);
	LCD_command(0x33);
	LCD_command(0x32);
	LCD_command(0x28);//function set
	LCD_command(0x06);//entry mode
	LCD_command(0x0c);//display on/off
	LCD_command(0x01);//clear screen
	_delay_ms(2);
}
void LCD_command(uint8 cmnd){
	uint8 send_command=0;
	send_command=(PORTA_Reg &0x0F)|(cmnd & 0xF0); //to send high nipple
	Writeport(LCD_data_port,send_command);//to set rs to command
	DIO_WriteChannel(LCD_RS,STD_Low);

	DIO_WriteChannel(LCD_E,STD_Higt);
	_delay_us(20);
	DIO_WriteChannel(LCD_E,STD_Low);
	_delay_ms(2);
	send_command=(PORTA_Reg &0x0F)|(cmnd<<4 );//to send low nipple
	Writeport(LCD_data_port,send_command);//to set rs to command

	DIO_WriteChannel(LCD_RS,STD_Low);
	DIO_WriteChannel(LCD_E,STD_Higt);
	_delay_us(20);
	DIO_WriteChannel(LCD_E,STD_Low);
	_delay_ms(2);



}
void LCD_data(uint8 data){
	uint8 send_data;
	send_data=(PORTA_Reg &0x0F)|(data & 0xF0); //to send high nipple
	Writeport(LCD_data_port,send_data);//to set rs to command
	DIO_WriteChannel(LCD_RS,STD_Higt);

	DIO_WriteChannel(LCD_E,STD_Higt);
	_delay_us(20);
	DIO_WriteChannel(LCD_E,STD_Low);
	_delay_ms(2);
	send_data=(PORTA_Reg &0x0F)|(data<<4 );//to send low nipple
	Writeport(LCD_data_port,send_data);//to set rs to command
	DIO_WriteChannel(LCD_RS,STD_Higt);

	DIO_WriteChannel(LCD_E,STD_Higt);
	_delay_us(20);
	DIO_WriteChannel(LCD_E,STD_Low);
	_delay_ms(2);

}
void LCD_String(char* string){
	uint8 i=0;
	while(string[i]!='\0'){
		LCD_data(string[i]);
		i++;
	}
}
void LCD_charpos(uint8 line,uint8 pos,uint8 data){
	switch(line){
		case 1:
		if(pos<16){
			LCD_command(0x80|(pos&0x0F));
		LCD_data(data);}
		break;
		case 2:
		if(pos<16){
			LCD_command(0xC0|(pos&0x0F));
		LCD_data(data);}
		break;

	}
}
void LCD_stringpos(uint8 line,uint8 pos,char* string){
	switch(line){
		case 1:
		if(pos<16){
			LCD_command(0x80|(pos&0x0F));
		LCD_String(string);}
		break;
		case 2:
		if(pos<16){
			LCD_command(0xC0|(pos&0x0F));
		LCD_String(string);}
		break;

	}
}
void LCD_SPchar(uint8 loc,uint8 *msg){
	uint8 i=0;
	if(loc<8)
	{
		LCD_command(0x40 +(loc*8));
		for(i=0;i<8;i++)
		{
			LCD_data(msg[i]);
		}
	}
}



#endif /* LCD_H_ */