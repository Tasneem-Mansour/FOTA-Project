/*
 * MNVIC_Program.c
 *
 *       Author: Yasmeen
 */

#include "BIT_Math.h"
#include "STD.h"
#include "LERROR_STATES.h"
#include "MNVIC_private.h"
#include "MNVIC_interface.h"
#include "MNVIC_config.h"


uint8 NVIC_G_u8GroupMode = NVIC_GroupMode_g16s0;

void MNVIC_voidEnableInterrupt(uint8 copy_u8IntNum)
{
	NVIC_REG->ISER[copy_u8IntNum / 32] = (1U << copy_u8IntNum % 32);
}


void MNVIC_voidDisableInterrupt(uint8 copy_u8IntNum)
{
	NVIC_REG->ICER[copy_u8IntNum / 32] = (1U << copy_u8IntNum % 32);
	
}


void MNVIC_voidEnableInterruptPending(uint8 copy_u8IntNum)
{
	NVIC_REG->ISPR[copy_u8IntNum / 32] = (1U << copy_u8IntNum % 32);
	
}

void MNVIC_voidDisableInterruptPinding(uint8 copy_u8IntNum)
{
	NVIC_REG->ICPR[copy_u8IntNum / 32] = (1U << copy_u8IntNum % 32);
	
}

uint8 MNVICE_u8IsInterruptActive(uint8 copy_u8IntNum)
{
	return GET_BIT(NVIC_REG->IABR[copy_u8IntNum / 32], copy_u8IntNum);

}

void MNVIC_voidInitInterruptGroup(NVIC_GroupMode_t copy_GropMode)
{
		 //Read  SCB_AIRCR First reset the regester first
	SCB_AIRCR = (VECTKEY | (copy_GropMode << 8));
}
 
void MNVIC_voidSetInterruptPriority(uint8 copy_u8IntNum,NVIC_GroupMode_t copy_GropMode, uint8 copy_u8IntGroup, uint8 copy_u8IntPrio){
	uint8 L_u8PrioValue = 0;
	switch(copy_GropMode){
		case NVIC_GroupMode_g16s0 : L_u8PrioValue =  copy_u8IntGroup; break;
		case NVIC_GroupMode_g8s2  : L_u8PrioValue = (copy_u8IntGroup << 1) | copy_u8IntPrio; break;
		case NVIC_GroupMode_g4s4  : L_u8PrioValue = (copy_u8IntGroup << 2) | copy_u8IntPrio; break;
		case NVIC_GroupMode_g2s8  : L_u8PrioValue = (copy_u8IntGroup << 3) | copy_u8IntPrio; break;
		case NVIC_GroupMode_g0s16 : L_u8PrioValue =  copy_u8IntPrio; break;
	}

	NVIC_REG->IPR[copy_u8IntNum] = L_u8PrioValue << 4;
}

void MNVIC_voidGenerateSoftwareInterrupt(uint8 copy_u8IntNum)
{
	NVIC_REG->STIR = (copy_u8IntNum << 4);
}
