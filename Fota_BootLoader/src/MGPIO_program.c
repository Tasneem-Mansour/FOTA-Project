/*
 * MGPIO_program.c
 *
 *       Author: Yasmeen
 */

#include "BIT_Math.h"
#include "STD.h"
#include "LERROR_STATES.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"
#include "MGPIO_config.h"


void MGPIO_voidSetPinMode(uint8 Copy_u8PortName ,uint8 Copy_u8PinNum ,uint8 Copy_u8Mode  ){
	
	switch(Copy_u8PortName)
	{
	  case _GPIOA_PORT : MGPIOA->MODER |= (uint32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case _GPIOB_PORT : MGPIOB->MODER |= (uint32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case _GPIOC_PORT : MGPIOC->MODER |= (uint32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  default :
		  break ;
    }
}


void MGPIO_voidSetPinOutPutType(uint8 Copy_u8PortName ,uint8 Copy_u8PinNum ,uint8 Copy_u8OutPutType  ){
	
	switch(Copy_u8PortName)
	{
	  case _GPIOA_PORT : MGPIOA->OTYPER |= (uint32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case _GPIOB_PORT : MGPIOB->OTYPER |= (uint32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case _GPIOC_PORT : MGPIOC->OTYPER |= (uint32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  default :
		  break ;
     }
	
}

void MGPIO_voidSetPinOutSpeed(uint8 Copy_u8PortName ,uint32 Copy_u8PinNum ,uint32 Copy_u8OutSpeed ){
	
	switch(Copy_u8PortName)
	{
	  case _GPIOA_PORT : MGPIOA->OSPEEDR |= (uint32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case _GPIOB_PORT : MGPIOB->OSPEEDR |= (uint32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case _GPIOC_PORT : MGPIOC->OSPEEDR |= (uint32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  default : /*ERROR*/ break ;
	}
}

void MGPIO_voidSetPullType(uint8 Copy_u8PortName ,uint32 Copy_u8PinNum ,uint32 Copy_u8PullType )
{
	
		switch(Copy_u8PortName)
	{
	  case _GPIOA_PORT : MGPIOA->PUPDR   |= (uint32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case _GPIOB_PORT : MGPIOB->PUPDR   |= (uint32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case _GPIOC_PORT : MGPIOC->PUPDR   |= (uint32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  default : /*ERROR*/ break ;
	}
	
}


uint8 MGPIO_u8ReadData(uint8 Copy_u8PORT ,uint8 Copy_u8PIN)
{
	uint8 L_u8Data = 0 ;
	switch(Copy_u8PORT)
	{ 
	  case _GPIOA_PORT :L_u8Data= GET_BIT(MGPIOA->IDR,Copy_u8PIN ) ; break;
	  case _GPIOB_PORT :L_u8Data= GET_BIT(MGPIOB->IDR,Copy_u8PIN ) ; break;
	  case _GPIOC_PORT :L_u8Data= GET_BIT(MGPIOC->IDR,Copy_u8PIN ) ; break;
	  
	  default :
		  break ;
		
	}
	return L_u8Data;
	
}

void MGPIO_voidWriteData(uint8 Copy_u8PortName ,uint8 Copy_u8PinNum ,uint8 Copy_u8State)
{
	if(Copy_u8State==HIGH)
	{
		switch(Copy_u8PortName)
		{
		case _GPIOA_PORT :  SET_BIT(MGPIOA ->ODR,Copy_u8PinNum); break;
		case _GPIOB_PORT :  SET_BIT(MGPIOB ->ODR,Copy_u8PinNum); break;
		case _GPIOC_PORT :  SET_BIT(MGPIOC ->ODR,Copy_u8PinNum); break;
		
		default : /*ERROR*/ break ;
		}
		
	}
	else{
		switch(Copy_u8PortName)
		{
		case _GPIOA_PORT :  CLR_BIT(MGPIOA ->ODR,Copy_u8PinNum); break;
		case _GPIOB_PORT :  CLR_BIT(MGPIOB ->ODR,Copy_u8PinNum); break;
		case _GPIOC_PORT :  CLR_BIT(MGPIOC ->ODR,Copy_u8PinNum); break;
		
		default : /*ERROR*/ break ;
		}
	}
}

void MGPIO_voidPinLock(uint8 Copy_u8PortNum ,uint8 Copy_u8PinNum )
{
  switch(Copy_u8PortNum)	
  {
  case _GPIOA_PORT  :
	  SET_BIT(MGPIOA->LCKR,Copy_u8PinNum );
	  SET_BIT(MGPIOA->LCKR,_LUCKED_PIN );
	  while(!(GET_BIT(MGPIOA->LCKR,_LUCKED_PIN)));

	  break ;

  case _GPIOB_PORT  :
	  SET_BIT(MGPIOB->LCKR,Copy_u8PinNum );
	  SET_BIT(MGPIOB->LCKR,_LUCKED_PIN );
	  while(!(GET_BIT(MGPIOB->LCKR,_LUCKED_PIN)));

	  break ; 

  case _GPIOC_PORT  :
	  SET_BIT(MGPIOC->LCKR,Copy_u8PinNum );
	  SET_BIT(MGPIOC->LCKR,_LUCKED_PIN );
	  while(!(GET_BIT(MGPIOC->LCKR,_LUCKED_PIN)));

	  break ;
  }
	
}

void MGPIO_vDirectSetReset(uint8 Copy_u8PortName , uint8 Copy_u8PinNum, uint8 Copy_u8State)
{
	if(Copy_u8State == HIGH)
	{
		switch (Copy_u8PortName)
		{
			case _GPIOA_PORT: MGPIOA->BSRR = (1U<<Copy_u8PinNum); break;
			case _GPIOB_PORT: MGPIOB->BSRR = (1U<<Copy_u8PinNum); break;
			case _GPIOC_PORT: MGPIOC->BSRR = (1U<<Copy_u8PinNum); break;
		}
	}
	else
	{
		Copy_u8PinNum += 16;
		switch (Copy_u8PortName)
		{
			case _GPIOA_PORT: MGPIOA->BSRR = (1U<<Copy_u8PinNum); break;
			case _GPIOB_PORT: MGPIOB->BSRR = (1U<<Copy_u8PinNum); break;
			case _GPIOC_PORT: MGPIOC->BSRR = (1U<<Copy_u8PinNum); break;
		}
	}
}

void MGPIO_voidSetPinAltFn( uint8 Copy_u8PortNum ,uint8 Copy_u8PinNum, uint8 Copy_u8ALF )
{
	if(Copy_u8PinNum <=7U)
	{
		switch(Copy_u8PortNum )
		{
			 case _GPIOA_PORT  : MGPIOA->AFRL |=(uint32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case _GPIOB_PORT  : MGPIOB->AFRL |=(uint32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case _GPIOC_PORT  : MGPIOC->AFRL |=(uint32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 default : break ;
		}
		
	}
	
	else
	{
	switch(Copy_u8PortNum )
		{
			 case _GPIOA_PORT  : MGPIOA->AFRH |=(uint32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;
			 case _GPIOB_PORT  : MGPIOB->AFRH |=(uint32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U ))); break ;
			 case _GPIOC_PORT  : MGPIOC->AFRH |=(uint32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;
			 default : break ;
		}
	}
}

void delay(uint32 delay_ms)
{

	for(int i=0;i<delay_ms;i++)
	{
		//Inline Assembly
		//Compiler Directive =>asm"assembly"
		asm("NOP");
	}
}
