/*
 * SYSTICK_Interface.h
 *
 *  Created on: May 31, 2023
 *      Author: hikal
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#define AHB    1
#define AHB_8  2

/*********STK_CTRL_BITS***********/
#define STKCTR_EN           0
#define STKCTR_TICK_INT     1
#define STKCTR_CLKSRC       2
#define STKCTR_COUNTFLAG    16



/********Init Timer*****/
void STK_voidInit(void);
/**********Busy Wait**********/
void STK_voidSetBusyWaitInterval(u32 Copy_u32Ticks);
/******************Single shoot(interrupt) ********/
void STK_voidSetSingleInterrupt(u32 Copy_u32Ticks,void (*PFunc)(void));
/******************Multi shoot********/
void STK_voidSetMultiInterrupt(u32 Copy_u32Ticks,void (*PFunc)(void));
/******************Stop timer********/
void STK_voidStop(void);

/******************Read timer value ********/
u32 STK_u8GetTimerVal(void);
/******************Timer_Handler********/

void Systick_voidCallBack(void (*PFunc)(void));


#endif /* SYSTICK_INTERFACE_H_ */
