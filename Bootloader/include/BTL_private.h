/*
 * BTL.private.h
 *
 *       Author: Yasmeen
 */

#ifndef BTL_PRIVATE_H
#define BTL_PRIVATE_H

static void BTL_voidParseRecord(void);
static void BTL_voidSetHighAddress(void);
static uint8 getHex(uint8 Copy_u8Asci);
static void BTL_voidCharReceived(uint8 rec);
static void BTL_voidRunAppCode(void);
static void BTL_voidRunSecondAppCode(void);
void choice_app(uint8 flag);
void handleReceivedData(uint8 x);
void Run_App(uint8 flag);
void handleRunData(uint8 x);

#endif
