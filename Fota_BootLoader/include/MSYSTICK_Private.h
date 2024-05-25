/*
 * MSYSTICK_Private.h
 *
 *      Author: Yasmeen
 */


#ifndef SYSTICK_REG_H_
#define SYSTICK_REG_H_

 
 #define    STK_BASE_ADRESS        0xE000E010

typedef struct{

	volatile uint32 CTRL ;
	volatile uint32 LOAD ;
	volatile uint32 VAL  ;
	volatile uint32 CALIB;

}SYSTICK;

#define MSTK ((volatile SYSTICK*)STK_BASE_ADRESS)

#endif /* SYSTICK_REG_H_ */
