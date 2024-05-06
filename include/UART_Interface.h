/*
 * UART_Interface.h
 *
 *  Created on: Jun 7, 2023
 *      Author: hikal
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


#include"UART_Private.h"



void  UART_voidInit(UART_CfgType * puart);
void  UART_voidSendChar(UART_CfgType * puart,u8 Copyu8_Frame);
void  UART_voidTransmit(UART_CfgType * puart,u8 *Copyu8_Frame,u8 Copyu8_BlockSize);
u8    UART_voidRecieve(UART_CfgType * puart);
u8 *  UART_u32AReceive(UART_CfgType * puart,u8 * Copy_u32MaxSize);
void  UART_voidTransmit_INT(UART_CfgType * puart,u8 *Copyu8_Frame,u8 Copyu8_BlockSize);
void   UART_voidRecieve_INT(UART_CfgType * puart,u8* data);

void UART_voidCallBack (void (*ptr)(UART_CfgType * UART_Cofigration6,u8* rx_data));
//void UART_voidCallBack (void (*ptr)(void));

//void UART_voidCallBack(UART_CallBack callback, UART_CfgType* ptrStruct, u8* ptrChar);




#endif /* UART_INTERFACE_H_ */
