/*
 * RCC_private.h
 *
 *      Author:Yasmeen
 */

#ifndef MRCC_PRIVATE_H
#define MRCC_PRIVATE_H


#define MRCC_BASE_ADDRESS     0x40023800

#define RCC_CR                      (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x00)))
#define RCC_PLLCFGR                 (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x04)))
#define RCC_CFGR                    (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x08)))
#define RCC_CIR                     (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x0C)))
#define RCC_AHB1RSTR                (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x10)))
#define RCC_AHB2RSTR                (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x14)))
#define RCC_APB1RSTR                (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x20)))
#define RCC_APB2RSTR                (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x24)))
#define RCC_AHB1ENR                 (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x30)))
#define RCC_AHB2ENR                 (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x34)))
#define RCC_APB1ENR                 (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x40)))
#define RCC_APB2ENR                 (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x44)))
#define RCC_AHB1LPENR               (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x50)))
#define RCC_AHB2LPENR               (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x54)))
#define RCC_APB1LPENR               (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x60)))
#define RCC_APB2LPENR               (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x64)))
#define RCC_BDCR                    (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x70)))
#define RCC_CSR                     (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x74)))
#define RCC_SSCGR                   (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x80)))
#define RCC_PLLI2SCFGR              (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x84)))
#define RCC_DCKCFGR                 (*(( volatile uint32* )(MRCC_BASE_ADDRESS + 0x8c)))

#define CSSON   19U

typedef struct
{
  volatile uint32 CR;
  volatile uint32 PLLCFGR;
  volatile uint32 CFGR;
  volatile uint32 CIR;
  volatile uint32 AHB1RSTR;
  volatile uint32 AHB2RSTR;
  volatile uint32 RESERVED0;
  volatile uint32 RESERVED1;
  volatile uint32 APB1RSTR;
  volatile uint32 APB2RSTR;
  volatile uint32 RESERVED2[2];
  volatile uint32 AHB1ENR;
  volatile uint32 AHB2ENR;
  volatile uint32 RESERVED3;
  volatile uint32 RESERVED4;
  volatile uint32 APB1ENR;
  volatile uint32 APB2ENR;
  volatile uint32 RESERVED5[2];
  volatile uint32 AHB1LPENR;
  volatile uint32 AHB2LPENR;
  volatile uint32 RESERVED6;
  volatile uint32 RESERVED7;
  volatile uint32 APB1LPENR;
  volatile uint32 APB2LPENR;
  volatile uint32 RESERVED8[2];
  volatile uint32 BDCR;
  volatile uint32 CSR;
  volatile uint32 RESERVED9[2];
  volatile uint32 SSCGR;
  volatile uint32 PLLI2SCFGR;
  volatile uint32 RESERVED10[1];
  volatile uint32 DCKCFGR;
}RCC_TypeDeff;


#define    MRCC     ((volatile RCC_TypeDeff *) (MRCC_BASE_ADDRESS))

#endif //MRCC_PRIVATE_H
