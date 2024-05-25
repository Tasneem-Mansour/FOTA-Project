/*
 * MNVIC_Interface.h
 *
 *      Author: Yasmeen
 */

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H


typedef enum{
    NVIC_GroupMode_g16s0 = 3,
    NVIC_GroupMode_g8s2,
    NVIC_GroupMode_g4s4,
    NVIC_GroupMode_g2s8,
    NVIC_GroupMode_g0s16
}NVIC_GroupMode_t;


void MNVIC_voidEnableInterrupt(uint8 copy_u8IntNum);
void MNVIC_voidDisableInterrupt(uint8 copy_u8IntNum);
void MNVIC_voidEnableInterruptPending(uint8 copy_u8IntNum);
void MNVIC_voidDisableInterruptPinding(uint8 copy_u8IntNum);
uint8   MNVIC_u8IsInterruptActive(uint8 copy_u8IntNum);
void MNVIC_voidInitInterruptGroup(NVIC_GroupMode_t copy_GropMode);
void MNVIC_voidSetInterruptPriority(uint8 copy_u8IntNum,NVIC_GroupMode_t copy_GropMode, uint8 copy_u8IntGroup, uint8 copy_u8IntPrio);
void MNVIC_voidGenerateSoftwareInterrupt(uint8 copy_u8IntNum);

#endif //NVIC_INTERFACE_H
