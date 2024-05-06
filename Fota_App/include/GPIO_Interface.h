/*
 * GPIO_Interface.h
 *
 *  Created on: May 29, 2023
 *      Author: hikal
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/*************Ports**************/
#define GPIO_PORTA       0
#define GPIO_PORTB       1
#define GPIO_PORTC       2

/*************Pins*************/
#define GPIOA_PIN0          0
#define GPIOA_PIN1          1
#define GPIOA_PIN2          2
#define GPIOA_PIN3          3
#define GPIOA_PIN4          4
#define GPIOA_PIN5          5
#define GPIOA_PIN6          6
#define GPIOA_PIN7          7
#define GPIOA_PIN8          8
#define GPIOA_PIN9          9
#define GPIOA_PIN10         10
#define GPIOA_PIN11         11
#define GPIOA_PIN12         12
#define GPIOA_PIN13         13
#define GPIOA_PIN14         14
#define GPIOA_PIN15         15


#define GPIOB_PIN0          0
#define GPIOB_PIN1          1
#define GPIOB_PIN2          2
#define GPIOB_PIN3          3
#define GPIOB_PIN4          4
#define GPIOB_PIN5          5
#define GPIOB_PIN6          6
#define GPIOB_PIN7          7
#define GPIOB_PIN8          8
#define GPIOB_PIN9          9
#define GPIOB_PIN10         10
#define GPIOB_PIN11         11
#define GPIOB_PIN12         12
#define GPIOB_PIN13         13
#define GPIOB_PIN14         14
#define GPIOB_PIN15         15

#define GPIOC_PIN0          0
#define GPIOC_PIN1          1
#define GPIOC_PIN2          2
#define GPIOC_PIN3          3
#define GPIOC_PIN4          4
#define GPIOC_PIN5          5
#define GPIOC_PIN6          6
#define GPIOC_PIN7          7
#define GPIOC_PIN8          8
#define GPIOC_PIN9          9
#define GPIOC_PIN10         10
#define GPIOC_PIN11         11
#define GPIOC_PIN12         12
#define GPIOC_PIN13         13
#define GPIOC_PIN14         14
#define GPIOC_PIN15         15


/*************PIN OUTPUT MODES   ********/
#define GPIO_u8_INPUT_MODE    0
#define GPIO_u8_OUTPUT_MODE   1
#define GPIO_u8_ALTF_MODE     2
#define GPIO_u8_ANALOG_MODE   3
/*************PIN OUTPUT TYPES   ********/
#define GPIO_u8_PUSH_PULL_TYPE   0b0
#define GPIO_u8_OPEN_DRAIN_TYPE  0b1

/*************PIN SPEED MODE   ********/
#define GPIO_u8_LOW_SPEED      0b00
#define GPIO_u8_MED_SPEED      0b01
#define GPIO_u8_HIGH_SPEED     0b10
#define GPIO_u8_VHIGH_SPEED    0b11
 /*************PULL_UP_DOWN********************/
#define GPIO_u8_PUP_PUD_FLOATING    0b00
#define GPIO_u8_PUP                 0b01
#define GPIO_u8_PUD                 0b10
/****************************************/
#define GPIO_u8_OUT_HIGH     0b1
#define GPIO_u8_OUT_LOW      0b0

/*************ALTF*******************/
#define  ATLF_0       0
#define  ATLF_1       1
#define  ATLF_2       2
#define  ATLF_3       3
#define  ATLF_4       4
#define  ATLF_5       5
#define  ATLF_6       6
#define  ATLF_7       7
#define  ATLF_8       8
#define  ATLF_9       9
#define  ATLF_10      10
#define  ATLF_11      11
#define  ATLF_12      12
#define  ATLF_13      13
#define  ATLF_14      14
#define  ATLF_15      15


/*************************FUNCTION PROTOTYPES**************/
/**
 *o/p type
 *        1-push_pull
 *        2_open drain
 */
void GPIO_voidSetPinOutType(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinOpType);

void GPIO_voidSetPinMode(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinMode);
void GPIO_voidSetPinSpeed(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinSpeed);
void GPIO_voidSetPinPUPD(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinPUPD);
void GPIO_voidSetPinVal(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinVal);

u8  GPIO_u8GetPinVal(u8 Copy_u8PortID,u8 Copy_u8PinID);


void GPIO_voidSetPinALTF(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinALTF);



#endif /* GPIO_INTERFACE_H_ */
