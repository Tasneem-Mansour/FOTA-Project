/*
 * MUSART_Program.c
 *
 *       Author: Yasmeen
 */

#include "BIT_Math.h"
#include "STD.h"
#include "USART_private.h"
#include "USART_config.h"
#include "USART_interface.h"
#include "MRCC_interface.h"
static void (*USART1_recieveCallback)(uint8 x);

extern uint8 y;
void MSUART_voidInit(void)
{

	/***********	UART_1		***********/
#if (UART1_USED == U_ENABLE)
	USART1_REG->BRR = UART1_BUAD_RATE;
	USART1_REG->CR2 |= (UART1_STOP_BITS << 12);
	USART1_REG->CR1.SBK = UART1_SEND_BREAK;
	USART1_REG->CR1.RE = UART1_RECEIVER;
	USART1_REG->CR1.TE = UART1_TRANSMITTER;
	USART1_REG->CR1.RXNEIE = UART1_RX_INT;
	USART1_REG->CR1.TCIE = UART1_T_COMP_INT;
	USART1_REG->CR1.PCE = UART1_PARITY_ENABLE;
	USART1_REG->CR1.PS = UART1_PARITY_MODE;
	USART1_REG->CR1.M = UART1_WORD_LEN;
	USART1_REG->CR1.OVER8	= UART1_OVER_SAMPLING;

#endif

	/***********	UART_2		***********/
#if (UART2_USED == U_ENABLE)
	USART2_REG->CR1.SBK = UART2_SEND_BREAK;
	USART2_REG->CR1.RE = UART2_RECEIVER;
	USART2_REG->CR1.TE = UART2_TRANSMITTER;
	USART2_REG->CR1.RXNEIE = UART2_RX_INT;
	USART2_REG->CR1.TCIE = UART2_T_COMP_INT;
	USART2_REG->CR1.PCE = UART2_PARITY_ENABLE;
	USART2_REG->CR1.PS = UART2_PARITY_MODE;
	USART2_REG->CR1.M = UART2_WORD_LEN;
	USART2_REG->CR1.OVER8	= UART2_OVER_SAMPLING;

	USART2_REG->BRR = UART2_BUAD_RATE;

	USART2_REG->CR2 |= (UART2_STOP_BITS << 12);
#endif

	/***********	UART_6		***********/
#if (UART6_USED == U_ENABLE)
	USART6_REG->BRR = UART6_BUAD_RATE;

	USART6_REG->CR2 |= (UART6_STOP_BITS << 12);

	USART6_REG->CR1.SBK = UART6_SEND_BREAK;
	USART6_REG->CR1.RE = UART6_RECEIVER;
	USART6_REG->CR1.TE = UART6_TRANSMITTER;
	USART6_REG->CR1.RXNEIE = UART6_RX_INT;
	USART6_REG->CR1.TCIE = UART6_T_COMP_INT;
	USART6_REG->CR1.PCE = UART6_PARITY_ENABLE;
	USART6_REG->CR1.PS = UART6_PARITY_MODE;
	USART6_REG->CR1.M = UART6_WORD_LEN;
	USART6_REG->CR1.OVER8	= UART6_OVER_SAMPLING;


#endif
}

/*******************************************************************************************************/
/*                                      02- MUSART_voidEnable                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_uint8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_uint8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MUSART_voidEnable(uint8 copy_uint8Index){
	switch(copy_uint8Index){
	case 1: USART1_REG -> CR1.UE = 1; break;
	case 2: USART2_REG -> CR1.UE = 1; break;
	case 6: USART6_REG -> CR1.UE = 1; break;
	}
}

/*******************************************************************************************************/
/*                                      03- MUSART_voidDisable                                         */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_uint8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_uint8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MUSART_voidDisable(uint8 copy_uint8Index){
	switch (copy_uint8Index)
	{
	case 1: USART1_REG -> CR1.UE = 0; break;
	case 2: USART2_REG -> CR1.UE = 0; break;
	case 6: USART6_REG -> CR1.UE = 0; break;
	}
}

/*******************************************************************************************************/
/*                                      04- MSUART_uint8SendData                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_uint8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_uint8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MUSART_uint8SendData(uint8 copy_uint8Index, uint8* copy_uint8Data, uint8 copy_uint8Len){

	UART_REG uhandler = MUSART_GetHandler(copy_uint8Index);
	for(uint8 counter = 0; counter < copy_uint8Len; counter++){
		uhandler ->DR = copy_uint8Data[counter];
		while(!GET_BIT(uhandler->SR, 6));
	}

}

/*******************************************************************************************************/
/*                                      05- MUSART_uint8ReadData                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_uint8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_uint8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


uint8 MUSART_uint8ReadData(uint8 copy_uint8Index){
	UART_REG uhandler = MUSART_GetHandler(copy_uint8Index);
	return (uint8) uhandler->DR;
}

/*******************************************************************************************************/
/*                                      01- MUSART_GetHandler                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_uint8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_uint8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


UART_REG MUSART_GetHandler(uint8 copy_uint8Index){
	UART_REG L_handle= (UART_REG) USART1_BASE_ADRESS;
	switch (copy_uint8Index)
	{
	case 1: L_handle =  (UART_REG) USART1_BASE_ADRESS; break;
	case 2: L_handle =  (UART_REG) USART2_BASE_ADRESS; break;
	case 6: L_handle =  (UART_REG) USART6_BASE_ADRESS; break;
	}
	return L_handle;
}

void MUSART1_voidSendCharSynch( uint8 Copy_uint8Char ){

	UART_REG uhandler = MUSART_GetHandler(1);

	uhandler -> DR = Copy_uint8Char ;

	while( GET_BIT( uhandler -> SR , 6 ) == 0 );

	CLR_BIT( uhandler -> SR , 6 );

}


uint8 MUSART1_uint8ReceiveCharSync( uint8 *  Copy_uint8DataCome ){
	UART_REG uhandler = MUSART_GetHandler(1);

	uint8 LOC_uint8Status = 1;

	if( GET_BIT( uhandler -> SR , 5 ) == 1 ){

		*Copy_uint8DataCome = uhandler -> DR ;
	}
	else
	{
		LOC_uint8Status = 0 ;
	}
	return LOC_uint8Status ;
}


void MUSART1_voidSendSrtingSynch( uint8 *  Copy_uint8String ){

	uint8 LOC_uint8Iterator = 0 ;

	while( Copy_uint8String[ LOC_uint8Iterator ] != '\0' ){

		MUSART1_voidSendCharSynch(  Copy_uint8String[ LOC_uint8Iterator ] );
		LOC_uint8Iterator++;

	}

}

void USART1_voidTransmit(uint8 data)
{
	USART1_REG->DR = data;
    while ((GET_BIT(USART1_REG->SR, 6)) == 0)
        ; /* Wait till transmission is complete */
}

void USART1_voidEnableRecieveInterrupt(void (*copy_ptr)(uint8 x))
{

    USART1_recieveCallback = copy_ptr;
    USART1_REG->CR1.RXNEIE=1;
   // SET_BIT((USART1_REG->CR1), 5); /* Enable Interrupt */
}
void USART1_IRQHandler(void)
{

    if ((GET_BIT(USART1_REG->SR, 5)))
    {
        /* Callback notification */
        USART1_recieveCallback(USART1_REG->DR);
    }
    y=1;
}

void USART1_voidDisableRecieveInterrupt (void)
{
USART1_REG->CR1.RXNEIE=0;
//	CLR_BIT((USART1_REG->CR1), 5); /* Disable Interrupt */
}
