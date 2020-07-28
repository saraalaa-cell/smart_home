/*
 * DIO_CFG.h
 *
 * Created: 28/07/2020 11:51:41 ص
 *  Author: FGstore
 */ 


#ifndef DIO_CFG_H_
#define DIO_CFG_H_


#include "STD_Types.h"
#include "DIO_Types.h"
#include "DIO_HW.h"
#include "Bit_Math.h"
#include "DIO.h"

#define PINCOUNT 32

void DIO_Init(void);
typedef struct{
	DIO_Dir PinDirection;
	STD_LevelTypes PinLevel;
}DIO_PinConfig;




const DIO_PinConfig PinConfig[] = {
	//PORTA
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	//PORTB
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	//PORTC
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	//PORTD
	{Output,STD_Low},
	{Output,STD_Low},
	{Input,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low},
	{Output,STD_Low}
};

void DIO_Init(){
	DIO_PORTS Portx;
	DIO_Channels ChannelPos;
	uint8 count = 0;
	for(count = DIO_ChannelA0;count<PINCOUNT;count++){
		Portx = count/8;
		ChannelPos = count%8;
		switch(Portx){
			case DIO_PORTA:
			if(PinConfig[count].PinDirection == Output){
				Set_Bit(DDRA_Reg,ChannelPos);
			}
			else{
				Clear_Bit(DDRA_Reg,ChannelPos);
			}
			break;
			case DIO_PORTB:
			if(PinConfig[count].PinDirection == Output){
				Set_Bit(DDRB_Reg,ChannelPos);
			}
			else{
				Clear_Bit(DDRB_Reg,ChannelPos);
			}
			break;
			case DIO_PORTC:
			if(PinConfig[count].PinDirection == Output){
				Set_Bit(DDRC_Reg,ChannelPos);
			}
			else{
				Clear_Bit(DDRC_Reg,ChannelPos);
			}
			break;
			case DIO_PORTD:
			if(PinConfig[count].PinDirection == Output){
				Set_Bit(DDRD_Reg,ChannelPos);
			}
			else{
				Clear_Bit(DDRD_Reg,ChannelPos);
			}
			break;
		}

	}
}


#endif /* DIO_CFG_H_ */