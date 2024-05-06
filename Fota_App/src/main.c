#include"LBIT_MATH.h"
#include"LSTD_TYPES.h"
#include"LERROR_STATES.h"
#include"stm32f401xx.h"
#include"MRCC_Interface.h"
#include"GPIO_Interface.h"
#include"NVIC_Interface.h"


#include"UART_Private.h"
#include"UART_Config.h"
#include"UART_Interface.h"
#include"SYSTICK_Interface.h"

u8 *rx_data;
u8 x,*str;
u8 size =11;
u8 i;


extern UART_CfgType  UART_Cofigration6 ;


int main(){



	RCC_voidInitCLK();
	RCC_voidEnablePeripherailClk(RCC_u8_AHB1_BUS,RCC_u8_GPIOA_EN);
	RCC_voidEnablePeripherailClk(RCC_u8_APB2_BUS,RCC_u8_SYSCFG_EN);//enable rcc for NIVC
	RCC_voidEnablePeripherailClk(RCC_u8_APB2_BUS,RCC_u8_USART6_EN);

	GPIO_voidSetPinMode(GPIO_PORTA, GPIOA_PIN0, GPIO_u8_OUTPUT_MODE);




	GPIO_voidSetPinMode(GPIO_PORTA, GPIOA_PIN11, GPIO_u8_ALTF_MODE);
	GPIO_voidSetPinMode(GPIO_PORTA, GPIOA_PIN12, GPIO_u8_ALTF_MODE);
	GPIO_voidSetPinALTF(GPIO_PORTA, GPIOA_PIN11, ATLF_8);
	GPIO_voidSetPinALTF(GPIO_PORTA, GPIOA_PIN12,ATLF_8);

	STK_voidInit();


	NIVC_voidEnableInterrupt(NVIC_UART6);
	UART_voidInit(&UART_Cofigration6);
	UART_voidTransmit(&UART_Cofigration6,"D",1);

	GPIO_voidSetPinVal(GPIO_PORTA, GPIOA_PIN0, GPIO_u8_OUT_HIGH);

	while(1)
	{

	}
}
