/*
 * NVIC_Prog.c
 *
 *  Created on: May 30, 2023
 *      Author: hikal
 */
#include"LSTD_TYPES.h"
#include"LBIT_MATH.h"
#include"LERROR_STATES.h"

#include"NVIC_Interface.h"
#include"NVIC_Private.h"
#include"NVIC_Config.h"
#include"stm32f401xx.h"

void NIVC_voidEnableInterrupt(u8 Copy_u8IntNum)
{
	/*REG_INDEX=Copy_u8IntNum/32
	  INT_Bit =Copy_u8IntNum %32  */
NVIC->ISER[Copy_u8IntNum/32]=(1 << (Copy_u8IntNum %32));
}
void NIVC_voidDisableInterrupt(u8 Copy_u8IntNum)
{
	NVIC->ICER[Copy_u8IntNum/32]=(1 << (Copy_u8IntNum %32));

}


void NIVC_voidSetPendingFlag(u8 Copy_u8IntNum)
{
	NVIC->ISPR[Copy_u8IntNum/32]=(1 << (Copy_u8IntNum %32));

}
void NIVC_voidClearPendingFlag(u8 Copy_u8IntNum)
{
	NVIC->ICPR[Copy_u8IntNum/32]=(1 << (Copy_u8IntNum %32));

}

void NIVC_voidSetInterruptPriorty(u8 Copy_u8IntNum,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority)
{
	NVIC->IPR[Copy_u8IntNum]=(Copy_u8GroupPriority<<6)|(Copy_u8SubPriority<<4);


}

u8  NIVC_u8_GetActiveFlag(u8 Copy_u8IntNum)
{
u8 	Local_u8_ActiveFlag=0;
Local_u8_ActiveFlag = GET_BIT(NVIC->IABR[Copy_u8IntNum/32],1 << (Copy_u8IntNum %32));

return Local_u8_ActiveFlag;
}
