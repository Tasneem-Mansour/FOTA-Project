/*
 * NVIC_Interface.h
 *
 *  Created on: May 30, 2023
 *      Author: hikal
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#define NVIC_UART1     37
#define NVIC_UART2     38
#define NVIC_UART6     71


void NIVC_voidEnableInterrupt(u8 Copy_u8IntNum);
void NIVC_voidDisableInterrupt(u8 Copy_u8IntNum);


void NIVC_voidSetPendingFlag(u8 Copy_u8IntNum);
void NIVC_voidClearPendingFlag(u8 Copy_u8IntNum);

void NIVC_voidSetInterruptPriorty(u8 Copy_u8IntNum,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority);

u8  NIVC_u8_GetActiveFlag(u8 Copy_u8IntNum);

#endif /* NVIC_INTERFACE_H_ */
