/*
 * MRCC_Interface.h
 *
 *  Created on: May 29, 2023
 *      Author: hikal
 */

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_



#define RCC_u8_AHB1_BUS    1
#define RCC_u8_AHB2_BUS    2
#define RCC_u8_APB1_BUS    3
#define RCC_u8_APB2_BUS    4


/***********AHB1 BUS Peripheral */
#define RCC_u8_GPIOA_EN   0
#define RCC_u8_GPIOB_EN   1
#define RCC_u8_GPIOC_EN   2
#define RCC_u8_GPIOD_EN   3
#define RCC_u8_GPIOE_EN   4
#define RCC_u8_GPIOH_EN   7
#define RCC_u8_CRC_EN     12
#define RCC_u8_DMA1_EN     21
#define RCC_u8_DMA2_EN     22


/***********AHB2 BUS Peripheral */
#define RCC_u8_OTGFS_EN      7

/***********APB1 BUS Peripheral */
#define RCC_u8_TIM2_EN    0
#define RCC_u8_TIM3_EN    1
#define RCC_u8_TIM4_EN    2
#define RCC_u8_TIM5_EN    3
#define RCC_u8_WWDG_EN    11
#define RCC_u8_SPI2_EN     14
#define RCC_u8_SPI3_EN     15
#define RCC_u8_USART2_EN   16
#define RCC_u8_I2C1_EN      21
#define RCC_u8_I2C2_EN      22
#define RCC_u8_I2C3_EN      23
#define RCC_u8_PWR_EN       28

/***********APB2 BUS Peripheral */
#define RCC_u8_TIM1_EN			0
#define RCC_u8_USART1_EN 		4
#define RCC_u8_USART6_EN 		5
#define RCC_u8_ADC1_EN   		8
#define RCC_u8_SDIO_EN   		11
#define RCC_u8_SPI1_EN   		12
#define RCC_u8_SPI4_EN   		13
#define RCC_u8_SYSCFG_EN 		14
#define RCC_u8_TIM9_EN   		16
#define RCC_u8_TIM10_EN  		17
#define RCC_u8_TIM11_EN  		18

/**
 * @fu RCC_voidInitCLK
 * @parmm(in) :N/A
 * @Des : This function is used to select the CLK System source and control
 *         the
 *
 **/
void RCC_voidInitCLK(void);

void RCC_voidEnablePeripherailClk(u8 Copy_u8BusID, u8 Copy_u8PeripheralNum);

void RCC_voidDisablePeripherailClk(u8 Copy_u8BusID, u8 Copy_u8PeripheralNum);


#endif /* MRCC_INTERFACE_H_ */
