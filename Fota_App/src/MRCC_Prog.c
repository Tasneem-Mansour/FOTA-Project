/*
 * MRCC_Prog.c
 *
 *  Created on: May 29, 2023
 *      Author: dina
 */

#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"

#include "LERROR_STATES.h"
#include "stm32f401xx.h"
#include "MRCC_Config.h"
#include "MRCC_Interface.h"
#include "MRCC_Private.h"

void RCC_voidInitCLK(void)
{

#if CLK_SRC ==HSE
	SET_BIT(RCC->CR,16);
	#if HSE_CLK== HSE_RC
		SET_BIT(RCC->CR,18);
	#elif HSE_CLK== HSE_Crystal
		CLR_BIT(RCC->CR,18);
	#endif

#elif CLK_SRC ==HSI
	SET_BIT(RCC->CR,0);
#elif CLK_SRC ==PLL
	SET_BIT(RCC->CR,24);
#else
	#error"Wrong Clock was selected"
#endif




}

void RCC_voidEnablePeripherailClk(u8 Copy_u8BusID, u8 Copy_u8PeripheralNum)
{
	switch (Copy_u8BusID)
	{
		case RCC_u8_AHB1_BUS: SET_BIT(RCC->AHB1ENR,Copy_u8PeripheralNum);     break;
		case RCC_u8_AHB2_BUS: SET_BIT(RCC->AHB2ENR,Copy_u8PeripheralNum);     break;
		case RCC_u8_APB1_BUS: SET_BIT(RCC->APB1ENR,Copy_u8PeripheralNum);     break;
		case RCC_u8_APB2_BUS: SET_BIT(RCC->APB2ENR,Copy_u8PeripheralNum);     break;

	}



}

void RCC_voidDisablePeripherailClk(u8 Copy_u8BusID, u8 Copy_u8PeripheralNum)
{
	switch (Copy_u8BusID)
	{
		case RCC_u8_AHB1_BUS: CLR_BIT(RCC->AHB1ENR,Copy_u8PeripheralNum);     break;
		case RCC_u8_AHB2_BUS: CLR_BIT(RCC->AHB2ENR,Copy_u8PeripheralNum);     break;
		case RCC_u8_APB1_BUS: CLR_BIT(RCC->APB1ENR,Copy_u8PeripheralNum);     break;
		case RCC_u8_APB2_BUS: CLR_BIT(RCC->APB2ENR,Copy_u8PeripheralNum);     break;

	}

}
