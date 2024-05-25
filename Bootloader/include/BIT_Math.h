/**************************************/
/* Description : STD.h                */
/* Author      : Yasmeen              */
/* Version     : 0.1v                 */
/* Date        : 31 Dec 2022          */
/* History     : 0.1v initial creation*/
/**************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG , BIT)     REG |= 1<<BIT
#define CLR_BIT(REG , BIT)     REG &= ~(1<<BIT)
#define TOG_BIT(REG , BIT)     REG ^= 1<<BIT
#define GET_BIT(REG , BIT)     ((REG >> BIT) & 1)

#define WRITE_BIT(REG , BIT, VAL)    CLR_BIT(REG,BIT) | (val << BIT)

 #define Set_BITS(REG,MSK)			(REG) |=  (MSK)
 #define Clr_BITS(REG,MSK)			(REG) &= ~(MSK)
 #define Toggle_BITS(REG,MSK)		(REG) ^=  (MSK)
 
 #define Set_ALL_BITS(REG)			(REG) =  (0xFFFFFFFF)
 #define Clr_ALL_BITS(REG)			(REG) =  (0x00000000)
 #define Toggle_ALL_BITS(REG)		(REG) ^= (0xFFFFFFFF)


 #endif /* BIT_MATH_H_ */
