/*
 * MRCC_Config.h
 *
 *  Created on: May 29, 2023
 *      Author: hikal
 */

#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_
/************************CLK_SRC_OPTIONS*************/
/* *
 * 1-HSE
 * 2-HSI
 * 3-PLL
 *
 * */

#define CLK_SRC HSI
/**************************HSE_CLK_OPTIONS************/
/*
 *		1-HSE_RC         (Enable bypass)
 *      2-HSE_Crystal    (Disable bypass)
 *
 * */
#define HSE_CLK  HSE_RC


#endif /* MRCC_CONFIG_H_ */
