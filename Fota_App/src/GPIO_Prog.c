/*
 * GPIO_Prog.c
 *
 *  Created on: May 30, 2023
 *      Author: hikal
 */
#include"LBIT_MATH.h"
#include"LSTD_TYPES.h"
#include"LERROR_STATES.h"
#include"stm32f401xx.h"
#include"GPIO_Interface.h"
#include"GPIO_Config.h"
#include"GPIO_Private.h"




void GPIO_voidSetPinOutType(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinOpType)
{

	if(Copy_u8PinOpType==GPIO_u8_PUSH_PULL_TYPE){

		switch(Copy_u8PortID)
			{
	case GPIO_PORTA:CLR_BIT(GPIOA->OTYPER, Copy_u8PinID )	;break;
	case GPIO_PORTB:CLR_BIT(GPIOB->OTYPER, Copy_u8PinID )	;break;
	case GPIO_PORTC:CLR_BIT(GPIOC->OTYPER, Copy_u8PinID )	;break;

	}
	}
	else if(Copy_u8PinOpType==GPIO_u8_OPEN_DRAIN_TYPE){

			switch(Copy_u8PortID)
				{
		case GPIO_PORTA:SET_BIT(GPIOA->OTYPER, Copy_u8PinID )	;break;
		case GPIO_PORTB:SET_BIT(GPIOB->OTYPER, Copy_u8PinID )	;break;
		case GPIO_PORTC:SET_BIT(GPIOC->OTYPER, Copy_u8PinID )	;break;

		}
		}

}

void GPIO_voidSetPinMode(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinMode){
	switch(Copy_u8PortID)
		{
		case GPIO_PORTA:GPIOA->MODER|= (Copy_u8PinMode << ( Copy_u8PinID * 2))	;break;
		case GPIO_PORTB:GPIOB->MODER|= (Copy_u8PinMode << ( Copy_u8PinID * 2))	;break;
		case GPIO_PORTC:GPIOC->MODER|= (Copy_u8PinMode << ( Copy_u8PinID * 2))	;break;

		}
}
void GPIO_voidSetPinSpeed(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinSpeed){

	switch(Copy_u8PortID)
		{
		case GPIO_PORTA:GPIOA->OSPEEDER|= (Copy_u8PinSpeed << ( Copy_u8PinID * 2))	;break;
		case GPIO_PORTB:GPIOB->OSPEEDER|= (Copy_u8PinSpeed << ( Copy_u8PinID * 2))	;break;
		case GPIO_PORTC:GPIOC->OSPEEDER|= (Copy_u8PinSpeed << ( Copy_u8PinID * 2))	;break;

		}

}
void GPIO_voidSetPinPUPD(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinPUPD){
	switch(Copy_u8PortID)
		{
		case GPIO_PORTA:GPIOA->PUPDR|= (Copy_u8PinPUPD << ( Copy_u8PinID * 2))	;break;
		case GPIO_PORTB:GPIOB->PUPDR|= (Copy_u8PinPUPD << ( Copy_u8PinID * 2))	;break;
		case GPIO_PORTC:GPIOC->PUPDR|= (Copy_u8PinPUPD << ( Copy_u8PinID * 2))	;break;

		}

}
void GPIO_voidSetPinVal(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinVal){

       if(Copy_u8PinVal==GPIO_u8_OUT_HIGH)
       {
	switch(Copy_u8PortID)
		{

		case GPIO_PORTA:SET_BIT(GPIOA->ODR,Copy_u8PinID);break;
		case GPIO_PORTB:SET_BIT(GPIOB->ODR,Copy_u8PinID);break;
		case GPIO_PORTC:SET_BIT(GPIOC->ODR,Copy_u8PinID);break;
	}
       }
	else if(Copy_u8PinVal==GPIO_u8_OUT_LOW)
	{
		switch(Copy_u8PortID)
			{
	case GPIO_PORTA:CLR_BIT(GPIOA->ODR,Copy_u8PinID);break;
	case GPIO_PORTB:CLR_BIT(GPIOB->ODR,Copy_u8PinID);break;
	case GPIO_PORTC:CLR_BIT(GPIOC->ODR,Copy_u8PinID);break;
}
		}
	}




u8  GPIO_u8GetPinVal(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
u8 Local_u8_PinVal=0;
	switch(Copy_u8PortID)
	{
	case GPIO_PORTA: Local_u8_PinVal=GET_BIT(GPIOA->IDR,Copy_u8PinID); break;
	case GPIO_PORTB: Local_u8_PinVal=GET_BIT(GPIOB->IDR,Copy_u8PinID); break;
	case GPIO_PORTC: Local_u8_PinVal=GET_BIT(GPIOC->IDR,Copy_u8PinID); break;

	}
return Local_u8_PinVal;

}


void GPIO_voidSetPinALTF(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinALTF)
{


	if(Copy_u8PinID>=0 && Copy_u8PinID<8)
	{    switch(Copy_u8PortID){
	    case GPIO_PORTA:GPIOA->AFRL|=(u32)(Copy_u8PinALTF<<(4*Copy_u8PinID));break;
	    case GPIO_PORTB:GPIOB->AFRL|=(u32)(Copy_u8PinALTF<<(4*Copy_u8PinID));break;
	    case GPIO_PORTC:GPIOC->AFRL|=(u32)(Copy_u8PinALTF<<(4*Copy_u8PinID));break;
	}
	}
	else {
		switch(Copy_u8PortID) {
		    case GPIO_PORTA :GPIOA->AFRH|=(u32)(Copy_u8PinALTF<<(4*(Copy_u8PinID %8)));break;
		    case GPIO_PORTB: GPIOB->AFRH|=(u32)(Copy_u8PinALTF<<(4*(Copy_u8PinID %8)));break;
		    case GPIO_PORTC: GPIOC->AFRH|=(u32)(Copy_u8PinALTF<<(4*(Copy_u8PinID %8)));break;

			}
}

}
