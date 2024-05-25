/*
 * MGPIO_private.h
 *
 *      Author: Yasmeen
 */


#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H


#define  GPIOA_BASE_ADDRESS         0x40020000
#define  GPIOB_BASE_ADDRESS         0x40020400
#define  GPIOC_BASE_ADDRESS         0x40020800 

#define GPIOA_MODER            (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x00)))
#define GPIOA_OTYPER           (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x04)))
#define GPIOA_OSPEEDR          (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x08)))
#define GPIOA_PUPDR            (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x0C)))
#define GPIOA_IDR              (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x10)))
#define GPIOA_ODR              (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x14)))
#define GPIOA_BSRR             (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x18)))
#define GPIOA_LCKR             (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x1C)))
#define GPIOA_AFRL             (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x20)))
#define GPIOA_AFRH             (*((volatile uint32 *)(GPIOA_BASE_ADDRESS+0x24)))

#define GPIOB_MODER            (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x00)))
#define GPIOB_OTYPER           (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x04)))
#define GPIOB_OSPEEDR          (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x08)))
#define GPIOB_PUPDR            (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x0C)))
#define GPIOB_IDR              (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x10)))
#define GPIOB_ODR              (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x14)))
#define GPIOB_BSRR             (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x18)))
#define GPIOB_LCKR             (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x1C)))
#define GPIOB_AFRL             (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x20)))
#define GPIOB_AFRH             (*((volatile uint32 *)(GPIOB_BASE_ADDRESS+0x24)))


#define GPIOC_MODER            (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x00)))
#define GPIOC_OTYPER           (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x04)))
#define GPIOC_OSPEEDR          (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x08)))
#define GPIOC_PUPDR            (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x0C)))
#define GPIOC_IDR              (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x10)))
#define GPIOC_ODR              (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x14)))
#define GPIOC_BSRR             (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x18)))
#define GPIOC_LCKR             (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x1C)))
#define GPIOC_AFRL             (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x20)))
#define GPIOC_AFRH             (*((volatile uint32 *)(GPIOC_BASE_ADDRESS+0x24)))


typedef struct{
	 volatile uint32 MODER  ;
	 volatile uint32 OTYPER ;
	 volatile uint32 OSPEEDR;
	 volatile uint32 PUPDR  ;
	 volatile uint32 IDR    ;
	 volatile uint32 ODR    ;
	 volatile uint32 BSRR   ;
	 volatile uint32 LCKR   ;
	 volatile uint32 AFRL   ;
	 volatile uint32 AFRH   ;
}GPIOx_t;


#define MGPIOA        ((GPIOx_t *) GPIOA_BASE_ADDRESS )
#define MGPIOB         ((GPIOx_t *) GPIOB_BASE_ADDRESS )
#define MGPIOC        ((GPIOx_t *) GPIOC_BASE_ADDRESS )


#define _LUCKED_PIN 16U

#endif //_GPIO_PRIVATE_H

