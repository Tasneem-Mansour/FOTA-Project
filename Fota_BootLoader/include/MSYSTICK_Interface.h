/*
 * MSYSTICK_Interface.h
 *
 *      Author: Yasmeen
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


#define MSTK_INT_EN   1
#define MSTK_INT_DIS  0


void MSTK_voidInit( void );
void MSTK_voidStart( uint32 Copy_PreloadValue );
void MSTK_voidINTStatus( uint8 Copy_u8Status );
uint8 MSTK_u8ReadFlag( void );
void MSTK_voidSetCallBack( void (*ptr)(void) );
void MSTK_voidSetIntervalSingle( uint32 Copy_u32Ticks, void (*Copy_ptr)(void) ) ;
uint32  MSTK_u32GetElapsedTime(void) ;
void _delay_us( uint32 Copy_u32Time );
void _delay_ms( uint32 Copy_u32Time );
void MSTK_voidStopTimer( void ) ;

#endif /* SYSTICK_INTERFACE_H_ */
