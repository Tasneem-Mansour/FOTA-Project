/*
 * USART_interface.h
 *
 *      Author: Yasmeen
 */


#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void MSUART_voidInit(void);

void MUSART_voidEnable(uint8 copy_uint8Index);

void MUSART_voidDisable(uint8 copy_uint8Index);

void MUSART_uint8SendData(uint8 copy_uint8Index, uint8* copy_uint8Data, uint8 copy_uint8Len);

uint8 MUSART_uint8ReadData(uint8 copy_uint8Index);

void MUSART1_voidSendCharSynch( uint8 Copy_uint8Char ) ;

void MUSART1_voidSendSrtingSynch( uint8 *  Copy_uint8String ) ;
uint8 MUSART1_uint8ReceiveCharSync( uint8* Copy_uint8DataCome ) ;
void USART1_voidEnableRecieveInterrupt(void (*copy_ptr)(uint8 x));
void USART1_voidTransmit(uint8 data);
void USART1_voidDisableRecieveInterrupt (void);


#endif
