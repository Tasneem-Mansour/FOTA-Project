/*
 * UART_Private.h
 *
 *  Created on: Jun 7, 2023
 *      Author: hikal
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#include"LBIT_MATH.h"
#include"LSTD_TYPES.h"
#include"LERROR_STATES.h"
#include"stm32f401xx.h"


#define UART_no_1    1
#define UART_no_2    2
#define UART_no_6    6

#define  interrupt_en     1
#define  interrupt_dis    0

#define    full_duplex    0
#define    half_duplex    1



typedef struct
{
u8 uart_number;
u8 duplex_type;
u8 interrupt_enable;
u32 Baud_Rate;
UART_RegDef_t * p_uart;

}UART_CfgType;





#endif /* UART_PRIVATE_H_ */
