/*
 * SYSTICK_Prog.c
 *
 *  Created on: May 31, 2023
 *      Author: hikal
 */
#include"LBIT_MATH.h"
#include"LERROR_STATES.h"
#include"LSTD_TYPES.h"
#include"stm32f401xx.h"
#include"SYSTICK_Config.h"
#include"SYSTICK_Interface.h"
#include"SYSTICK_Private.h"

static void (* Systick_CallBack )(void);

static  u8 STK_TimeMode;
void STK_voidInit(void)
{

	/**********SELECT CLK SOURCE****/
#if CLK_SRC_SELECT ==AHB
	SET_BIT(SYSTICK->CTRL,STKCTR_CLKSRC);
	//SYSTICK->CTRL=0X00000004;
#elif CLK_SRC_SELECT==AHB_8
	//CLR_BIT(SYSTICK->CTRL,STKCTR_CLKSRC);
	SYSTICK->CTRL=0X00000000;
#else
	#error"WRONG CLK_SOURCE"
#endif
}


void STK_voidSetBusyWaitInterval(u32 Copy_u32Ticks)
{
	//set the load value
	SYSTICK->LOAD=Copy_u32Ticks;
	//start timer
	SET_BIT(SYSTICK->CTRL,STKCTR_EN);
	//wait flag
	while(GET_BIT(SYSTICK->CTRL,STKCTR_COUNTFLAG)==0);
	//once flag is set ->stop timer /reset load value
	CLR_BIT(SYSTICK->CTRL,STKCTR_EN);
	SYSTICK->LOAD=0;
	SYSTICK->VAL=0;


}
void STK_voidSetSingleInterrupt(u32 Copy_u32Ticks,void (*PFunc)(void))

{

	    //set the load value
		SYSTICK->LOAD=Copy_u32Ticks;

		//save the ptr to function
		Systick_CallBack=PFunc;

		STK_TimeMode=SYSTICK_TimerSingle;
		//Enable Interrupt
		SET_BIT(SYSTICK->CTRL,STKCTR_TICK_INT);
		//start timer
		SET_BIT(SYSTICK->CTRL,STKCTR_EN);
}
void STK_voidSetMultiInterrupt(u32 Copy_u32Ticks,void (*PFunc)(void))

{
	 //set the load value
			SYSTICK->LOAD=Copy_u32Ticks;

			//save the ptr to function
			Systick_CallBack=PFunc;

			STK_TimeMode=SYSTICK_TimerMulti;
			//Enable Interrupt
			SET_BIT(SYSTICK->CTRL,STKCTR_TICK_INT);
			//start timer
			SET_BIT(SYSTICK->CTRL,STKCTR_EN);
}



void STK_voidStop(void)
{
	/*****DISABLE SYSTICK***********/
	CLR_BIT(SYSTICK->CTRL,STKCTR_TICK_INT);
	//stop timer /reset load value
		CLR_BIT(SYSTICK->CTRL,STKCTR_EN);
		SYSTICK->LOAD=0;
		SYSTICK->VAL=0;
}


u32 STK_u8GetTimerVal(void)
{
u32  Local_u32TimerVal=0;
Local_u32TimerVal =SYSTICK->VAL;


return Local_u32TimerVal;
}

void Systick_voidCallBack(void (*PFunc)(void))
{
	Systick_CallBack=PFunc;

}


void SysTick_Handler(void)
{
	if(STK_TimeMode==SYSTICK_TimerSingle)
	{

		//STK_voidStop();
		// Disable Tnterrupt
				// SIngle Mode => Once The Isr is triggered /
				CLR_BIT(SYSTICK->CTRL,1);

				//Stop Timer
				CLR_BIT(SYSTICK->CTRL,0);
				SYSTICK->LOAD = 0;
				SYSTICK->VAL   = 0;
	}

	//execute the callback
	Systick_CallBack();
	//clear flag
	CLR_BIT(SYSTICK->CTRL,STKCTR_COUNTFLAG);

}
