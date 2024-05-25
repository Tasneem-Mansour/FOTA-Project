
#include "STD.h"
#include "BIT_Math.h"

#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_Interface.h"
#include "MEXTI_interface.h"
#include "MSYSTICK_Interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "USART_interface.h"

#include "MFPEC_Interface.h"

#include "BTL_inteface.h"
#include "BTL_private.h"
#include "BTL_config.h"

volatile uint8 g_recieveBuffer[500] = {0}   ;
volatile uint8 g_recieveCounter     =  0    ;
volatile uint16 g_data[500]   = {0}        ;
volatile uint32 g_address  ;

volatile uint8 g_lineReceivedFlag = 0;
volatile uint8 g_finishReceiveFlag = 0;

typedef void (*Function_t)(void) ;

Function_t  Addr_To_Call = 0; 
Function_t Addr_To_Call2 = 0;
static uint8 Data;
uint8 x=1;
uint8 y=0;
uint8 dina;
//
//void handleReceivedData(uint8 x)
//{
//	if(x=='A')
//	{
//		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_6,HIGH);
//		MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunAppCode );   //edit time
//	}
//
//	else if(x=='B')
//	{
//
//		MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunSecondAppCode );
//		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_7,HIGH);
//	}
//	else
//	{
//
//		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_6,HIGH);
//	}
//}

// void handleReceivedData(uint8 x)
// {
//     Data = x;
//     choice_app(Data);
// }
//
// void handleRunData(uint8 data)
// {
//     data =Data ;
//     Run_App(Data);
// }

//void choice_app(uint8 x)
//{
//	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_3,HIGH);
//	Data = x;
//	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_5,HIGH);
//	if(Data=='A')
//	{
//		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_7,HIGH);
//		MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunAppCode );
//	}
//
//	else
//	{
//		MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunSecondAppCode );
//	}
//}
//
//void Run_App(uint8 flag)
//{
//	flag =Data ;
//		if(flag=='A')
//		{
//			BTL_voidRunAppCode();
//		}
//
//		else if(flag=='B')
//		{
//			BTL_voidRunSecondAppCode();
//		}
//}

void BTL_voidInit(void)
{

	MRCC_voidInitSystemClk();
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_FPEC ) ;
	MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_USART1);
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_GPIOA ) ;
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_GPIOB ) ;

	//UART init
	MSUART_voidInit();
	MUSART_voidEnable(1);
	MUSART_uint8SendData(1,(uint8*)"felfel",6);
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_9, _MODE_ALTF);  
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_10, _MODE_ALTF); 
	MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_9, _ALTFN_7);   
	MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_10, _ALTFN_7);  

	for(uint8 PIN = 0 ;PIN <=7 ;PIN++ )
	{
		MGPIO_voidSetPinMode(_GPIOA_PORT, PIN, _MODE_OUTPUT) ;
		MGPIO_voidSetPinOutPutType(_GPIOA_PORT,PIN,_OUTPUT_TYPE_PUSH_PULL);
		MGPIO_voidSetPinOutSpeed(_GPIOA_PORT, PIN, _OUTPUT_SPEED_LOW);
	}



	//MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunAppCode );   //8

	MNVIC_voidEnableInterrupt(37);
//	while(y==0)
//	{
//		USART1_voidEnableRecieveInterrupt(handleReceivedData);
//		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_5,HIGH);
//	}

	//USART1_voidDisableRecieveInterrupt();
	//MNVIC_voidEnableInterrupt(37);
	while(y==0)   //New
	{
		y= MUSART1_uint8ReceiveCharSync(&x);

	}
	//MGPIO_voidWriteData(_GPIOA_PORT, _PIN_3,HIGH);

	if(x=='A')
	{
		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_5,HIGH);
		MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunAppCode );
	}

	else if(x=='B')
	{
		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_1,HIGH);
		MSTK_voidSetIntervalSingle( BTL_TIMEOUT*1000000 , BTL_voidRunSecondAppCode );
	}
	y=0;
//	else
//	{
//
//		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_7,HIGH);
//	}


	//USART1_voidEnableRecieveInterrupt(BTL_voidCharReceived);  //fun

	while(y==0)   //New
	{
		y= MUSART1_uint8ReceiveCharSync(&dina);
	}
	BTL_voidCharReceived(dina);
}

void BTL_voidRun(void)
{
	while( g_finishReceiveFlag == 0 )  //not finish receive
	{
		if( g_lineReceivedFlag == 1 )
		{

			switch(g_recieveBuffer[g_recieveCounter])
			{
			case BTL_DATA_START_CHAR: //only one time
				g_recieveCounter = 0;
				MSTK_voidStopTimer();
				MFPEC_voidEraseAppArea();
				USART1_voidTransmit(BTL_READ_CONFIRM_CHAR);
				break;
			case BTL_LINE_BREAK_CHAR:
				BTL_voidParseRecord();  //to burn record and return counter zero to start receive again
				g_recieveCounter = 0;
				USART1_voidTransmit(BTL_READ_CONFIRM_CHAR);
				break;
			default:
				break;
			}
			g_lineReceivedFlag = 0;  //to continue check
		}
	}

	USART1_voidDisableRecieveInterrupt();/*******/
	//BTL_voidRunAppCode();
	//MGPIO_voidWriteData(_GPIOA_PORT, _PIN_5,HIGH);  /***************/
	//USART1_voidEnableRecieveInterrupt(Run_App);

	if(x=='A')
	{
		BTL_voidRunAppCode();
	}

	else if(x=='B')
	{
		BTL_voidRunSecondAppCode();
	}

	//MGPIO_voidWriteData(_GPIOA_PORT, _PIN_7,HIGH); /*******************/
}

static void BTL_voidRunAppCode(void)
{

#define SCB_VTOR  *((volatile uint32 *)0xE000ED08)

	SCB_VTOR     = 0x08004000 ;
	Addr_To_Call = *(Function_t *)0x08004004 ;
	Addr_To_Call();

}

static void BTL_voidRunSecondAppCode(void)
{

#define SCB_VTOR  *((volatile uint32 *)0xE000ED08)

	SCB_VTOR     =  0x0800C000 ;
	Addr_To_Call = *(Function_t *)0x0800C004 ;
	Addr_To_Call();

}

/*
volatile uint8 g_lineReceivedFlag = 0;
volatile uint8 g_finishReceiveFlag = 0;
*/

static void BTL_voidCharReceived(uint8 rec)
{
	g_recieveBuffer[g_recieveCounter] = rec;
	switch (rec)
	{
	case BTL_DATA_START_CHAR:
	case BTL_LINE_BREAK_CHAR:
		g_lineReceivedFlag = 1;
		break;
	case BTL_DATA_END_CHAR:
		g_finishReceiveFlag = 1;
		break;
	default:
		g_recieveCounter++;
		break;
	}
}

static uint8   getHex ( uint8 Copy_u8Asci )
{

	uint8 LOC_u8Result = 0 ;

	if( ( Copy_u8Asci >= 48 ) && ( Copy_u8Asci <= 57 ) )
	{

		LOC_u8Result = Copy_u8Asci - 48 ;

	}
	else
	{

		LOC_u8Result = Copy_u8Asci - 55 ;

	}
	return LOC_u8Result ;
}

static void BTL_voidParseRecord(void)
{
	uint8 CC, i;
	uint8 dataDigits[4];
	uint8 dataCounter = 0;

	switch (getHex(g_recieveBuffer[8]))
	{

	case 4:
		BTL_voidSetHighAddress();
		break;

	case 1: 
		break;

	case 0:
		CC = (getHex(g_recieveBuffer[1]) << 4) | getHex(g_recieveBuffer[2]);

		dataDigits[0] = getHex(g_recieveBuffer[3]);
		dataDigits[1] = getHex(g_recieveBuffer[4]);
		dataDigits[2] = getHex(g_recieveBuffer[5]);
		dataDigits[3] = getHex(g_recieveBuffer[6]);

		g_address = g_address & 0xFFFF0000;
		g_address = g_address |
				(dataDigits[3]) |
				(dataDigits[2] << 4) |
				(dataDigits[1] << 8) |
				(dataDigits[0] << 12);

		for (i = 0; i < CC / 2; i++)
		{
			dataDigits[0] = getHex(g_recieveBuffer[4 * i + 9]);
			dataDigits[1] = getHex(g_recieveBuffer[4 * i + 10]);
			dataDigits[2] = getHex(g_recieveBuffer[4 * i + 11]);
			dataDigits[3] = getHex(g_recieveBuffer[4 * i + 12]);
			g_data[dataCounter] = (dataDigits[3] << 8) |
					(dataDigits[2] << 12) |
					(dataDigits[1] << 0) |
					(dataDigits[0] << 4);
			dataCounter++;
		}

		if (CC % 2 != 0)
		{
			dataDigits[0] = getHex(g_recieveBuffer[4 * (CC / 2) + 9]);
			dataDigits[1] = getHex(g_recieveBuffer[4 * (CC / 2) + 10]);
			g_data[dataCounter] = 0xFF00 | (dataDigits[0] << 4) | (dataDigits[1] << 0);
			MFPEC_voidFlashWrite(g_address, (uint16 *)g_data, CC / 2 + 1);
		}
		else
		{
			MFPEC_voidFlashWrite(g_address, (uint16 *)g_data, CC / 2);
		}

		break;
	default:
		break;
	}

}

static void BTL_voidSetHighAddress(void)
{
	g_address = (getHex(g_recieveBuffer[9]) << 28) |
			(getHex(g_recieveBuffer[10]) << 24) |
			(getHex(g_recieveBuffer[11]) << 20) |
			(getHex(g_recieveBuffer[12]) << 16);
}

