/*
 * USART_private.h
 *
 *      Author: Yasmeen
 */

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H



#define USART1_BASE_ADRESS     0x40011000UL
#define USART2_BASE_ADRESS     0x40014400UL
#define USART6_BASE_ADRESS     0x40011400UL



/*******************************************************************************************************/
/*                                       Register Definitions                                          */
/*-----------------------------------------------------------------------------------------------------*/
/*     - Developer can't Edit in it                                                                    */
/*     - Register _ Defination		                                                                   */
/*     - Design :                                                                                      */
/*    				- #define	:	NO                                                                 */
/*    				- Union		:	NO                                                                 */
/*    				- Struct	:	YES                                                                */
/*                                                                                                     */
/*******************************************************************************************************/


typedef struct{
    uint32 SBK       :1;
    uint32 RWU       :1;
    uint32 RE        :1;
    uint32 TE        :1;
    uint32 IDLEIE    :1;
    uint32 RXNEIE    :1;
    uint32 TCIE      :1;
    uint32 TXEIE     :1;
    uint32 PEIE      :1;
    uint32 PS        :1;
    uint32 PCE       :1;
    uint32 WAKE      :1;
    uint32 M         :1;
    uint32 UE        :1;
    uint32 RESERVED  :1;
    uint32 OVER8     :1;
    uint32 RESERVED2 :16;
}UART_CR1;


typedef struct{

    uint32 SR;
    uint32 DR;
    uint32 BRR;
    UART_CR1 CR1;
    uint32 CR2;
    uint32 CR3;
    uint32 GTPR;
}UART_t;

/*******************************************************************************************************/
/*                                   Struct Macros Base Address Of USARTx                              */
/*******************************************************************************************************/

typedef    volatile UART_t* UART_REG ;

#define     USART1_REG    ((volatile UART_t*)(USART1_BASE_ADRESS))
#define     USART2_REG    ((volatile UART_t*)(USART2_BASE_ADRESS))
#define     USART6_REG    ((volatile UART_t*)(USART6_BASE_ADRESS))

static UART_REG MUSART_GetHandler(uint8 copy_u8Index);


#endif
