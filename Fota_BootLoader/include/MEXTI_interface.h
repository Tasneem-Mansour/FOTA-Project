/*
 * MEXIT_interface.h
 *
 *      Author:Yasmeen
 */

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


#define EXTI0     0
#define EXTI1     1

#define   RISING_EDGE     0

#define   FALLING_EDGE   1


#define    ON_CHANGE       2

void MEXTI_voidInit(void);
void MEXTI_voidSetSignalLatch(uint8 Copy_Exti_Line ,uint8 Copy_EXTI_Sense_Mode );
void MEXTI_voidEnableEXTI(uint8 Copy_u8Line);
void MEXTI_voidDisableEXTI(uint8 Copy_u8Line);
void MEXIT_voidSoftwareInterrput(uint8 Copy_u8Line);
void MEXTI0_voidSetCallBack( void (*ptr) (void));
void MEXTI1_voidSetCallBack( void (*ptr) (void));
void MEXTI_voidSetEXTIConfiguration(uint8 Copy_u8ExtiLine , uint8 Copy_u8GpioPortNum );


#endif  //EXTI_INTERFACE_H
