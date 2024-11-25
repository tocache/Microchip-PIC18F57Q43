/* 
 * File: MAX7219.h  
 * Author: Kalun Lau 
 * Comments:
 * Revision history: 
 * 19/10/2024 First release
 */ 

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAX7219_LIB_H
#define	MAX7219_LIB_H

#define max7219_cs LATCbits.LATC0
#define max7219_clk LATEbits.LATE0
#define max7219_data LATEbits.LATE1
#define _XTAL_FREQ 32000000UL

#define COM_SHUTDOWN 0x0C
#define COM_TEST 0x0F
#define COM_INTENSITY 0x0A
#define COM_DECMODE 0x09
#define COM_SCANLIMIT 0x0B

void MAX7219_Init();
void MAX7219_WriteData(unsigned char comando, unsigned char dato);
void MAX7219_WriteData2(unsigned char comando, unsigned char dato);

#endif	/* MAX7219_LIB_H */

