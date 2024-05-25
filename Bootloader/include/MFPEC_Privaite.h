/*
 * MFPEC_Privaite.h
 *
 *      Author:Yasmeen
 */

#ifndef MFPEC_PRIVAITE_H_
#define MFPEC_PRIVAITE_H_


typedef struct{

	volatile uint32 ACR      ;
	volatile uint32 KEYR     ;
	volatile uint32 OPTKEYR  ;
	volatile uint32 SR       ;
	volatile uint32 CR       ;
	volatile uint32 OPTCR    ;
}FPEC_Type;

#define MFPEC  ((volatile FPEC_Type*)0x40023C00)
#define  FPEC_SECTOR_MASK            0xFFFFFF87
#define FPEC_Flash_WRITE_SIZE_MASK   0xFFFFFCFF


#define WRITE_BYTE             0
#define WRITE_HALF_WORD        1
#define WRITE_WORD             2
#define WRITE_DOUBLE_WORD      3

#endif
