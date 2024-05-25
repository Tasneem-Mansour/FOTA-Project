/*
 * MFPEC_Interface.h
 *
 *      Author: Yasmeen
 */

#ifndef MFPEC_INTERFACE_H_
#define MFPEC_INTERFACE_H_


void MFPEC_voidEraseAppArea(void) ;
void MFPEC_voidSectorErase   ( uint8 Copy_u8SectorNumber ) ;
void MFPEC_voidFlashWrite( uint32 Copy_u32Address , uint16 * Copy_u16Data , uint8 Copy_u8DataLength ) ;

#endif /* MFPEC_INTERFACE_H_ */
