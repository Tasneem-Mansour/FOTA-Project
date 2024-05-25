/*
 * MNVIC_Private.h
 *
 *      Author: Yasmeen
 */


#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


#define NVIC_BASE_ADDRESS    0xE000E100

typedef struct
{
	uint32 ISER[8];
	uint32 RESERVED0[24];
	uint32 ICER[8];
	uint32 RSERVED1[24];
	uint32 ISPR[8];
	uint32 RESERVED2[24];
	uint32 ICPR[8];
	uint32 RESERVED3[24];
	uint32 IABR[8];
	uint32 RESERVED4[56];
	uint8  IPR[240];
	uint32 RESERVED5[580];
	uint32 STIR;
} NVIC_t;


/*******************************************************************************************************/
/*                                   Struct Macros Base Address Of NVIC                                */
/*******************************************************************************************************/

#define     NVIC_REG    ((volatile NVIC_t*)(NVIC_BASE_ADDRESS))

#define     SCB_AIRCR   (*(volatile uint32*) 0xE000ED0C)

#define     VECTKEY     0x05FA0000

#endif // GPIO_PRIVATE_H
