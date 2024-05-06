/*
 * UART_Prog.c
 *
 *  Created on: Jun 7, 2023
 *      Author: Dina
 */

#include"stdlib.h"
#include"LBIT_MATH.h"
#include"LSTD_TYPES.h"
#include"LERROR_STATES.h"
#include"stm32f401xx.h"
#include"MRCC_Interface.h"
#include"GPIO_Interface.h"

#include"SYSTICK_Interface.h"
#include"UART_Private.h"
#include"UART_Config.h"
#include"UART_Interface.h"

 extern UART_CfgType * puart;
 extern u8* P_char;

 extern UART_CfgType * UART_Cofigration6;
 extern u8* rx_data;
u8  *G_u8AMessage ;
//static void (*UART_CallBack)(UART_CfgType * puart,u8*  char);

void  UART_voidInit(UART_CfgType * puart)
{
	//Enable UART
	puart->p_uart->CR1.UE=1;
	//Enable Tx
	puart->p_uart->CR1.TE=1;
	//Enable Rx
	puart->p_uart->CR1.RE=1;
	// select Word length (8-bit)
	puart->p_uart->CR1.M=0;
	//select Buad Rate (9600)->BRR - CLK ->16MHz
	puart->p_uart->BRR=puart->Baud_Rate;
	//UART1->BRR=0x683 ;

	if(puart->duplex_type== half_duplex){
		//select half duplex selection (HDSEL ->bit3)
		SET_BIT(puart->p_uart->CR3,3);
	}

	if(puart->interrupt_enable==interrupt_en)
	{
		puart->p_uart->CR1.RXNEIE=1;
		// IDLEIE: IDLE interrupt enable
		puart->p_uart->CR1.IDLEIE=1;


	}


}
void  UART_voidSendChar(UART_CfgType * puart,u8 Copyu8_Frame)
{


	while(!GET_BIT(puart->p_uart->SR,6));//TC
	puart->p_uart->DR=Copyu8_Frame;
	STK_voidSetBusyWaitInterval(30000);

}
void  UART_voidTransmit(UART_CfgType * puart,u8 *Copyu8_Frame,u8 Copyu8_BlockSize)
{


	for(u8 i=0;i<Copyu8_BlockSize;i++)
	{
		while(!GET_BIT(puart ->p_uart->SR,6));//TC
		puart ->p_uart->DR=Copyu8_Frame[i];

	}
	STK_voidSetBusyWaitInterval(30000);

}
u8    UART_voidRecieve(UART_CfgType * puart)
{


	static u8 Copyu8_RChar;


	while(!GET_BIT(puart ->p_uart->SR,5));
	Copyu8_RChar=(puart ->p_uart->DR );


	return  Copyu8_RChar;


}
u8 *  UART_u32AReceive(UART_CfgType * puart,u8 * Copy_u32MaxSize)
{

	u8 L_u32Itterator = 0;
	G_u8AMessage=(u8 *)malloc(11* sizeof(u8));
	/* Wait for Data Receiving */
	while(!GET_BIT(puart ->p_uart->SR, 5));
	while(GET_BIT(puart ->p_uart->SR, 5)){
		G_u8AMessage[L_u32Itterator] =puart->p_uart->DR;

		L_u32Itterator++;
	}


	return G_u8AMessage;
}


void  UART_voidTransmit_INT(UART_CfgType * puart,u8 *Copyu8_Frame,u8 Copyu8_BlockSize)
{

	//set TXEIE: TXE interrupt enable
	puart->p_uart->CR1.TXEIE=1;

	// IDLEIE: IDLE interrupt enable
	puart->p_uart->CR1.IDLEIE=1;



}
void   UART_voidRecieve_INT(UART_CfgType * puart,u8* data)
{
//	//set RXEIE: TXE interrupt enable
//	puart->p_uart->CR1.RXNEIE=1;
//	// IDLEIE: IDLE interrupt enable
//	puart->p_uart->CR1.IDLEIE=1;

		if(puart->p_uart->SR & (1 << 5))
			{
				data = puart->p_uart->DR;

			}

}

void UART_voidCallBack (void (*ptr)(UART_CfgType * UART_Cofigration6,u8* rx_data))
{
	//Notify Interrupt Requested
	ptr(UART_Cofigration6,rx_data);

}
//void USART6_IRQHandler (void)
//{
//	UART_CallBack();
//
//}

