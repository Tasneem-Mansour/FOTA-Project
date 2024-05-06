/*
 * UART_Config.c
 *
 *  Created on: Oct 12, 2023
 *      Author: hikal
 */
#include"LBIT_MATH.h"
#include"LSTD_TYPES.h"
#include"LERROR_STATES.h"

#include"stm32f401xx.h"

#include"UART_Config.h"
#include"UART_Interface.h"
#include"UART_Private.h"



UART_CfgType  UART_Cofigration1 =
{
	.Baud_Rate=0x683,
	.duplex_type=half_duplex,
	.interrupt_enable=interrupt_dis,
	.uart_number=UART_no_1,
	.p_uart=UART1

};

UART_CfgType  UART_Cofigration6 =
{
	.Baud_Rate=0x683,
	.duplex_type=half_duplex,
	.interrupt_enable=interrupt_dis,
	.uart_number=UART_no_6,
	.p_uart=UART6

};
