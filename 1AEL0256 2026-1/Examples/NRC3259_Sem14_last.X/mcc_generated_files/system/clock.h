/**
 * CLOCK Generated Driver Header File 
 * 
 * @file clock.h
 * 
 * @defgroup clockdriver Clock Driver
 * 
 * @brief This file contains the API prototypes and other data types for the Clock driver.
 *
 * @version Driver Version 2.0.4
 *
 * @version Package Version 4.3.7
 *
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef CLOCK_H
#define	CLOCK_H

#ifndef _XTAL_FREQ
/**
    @ingroup clock control 
    @def system frequency
    @misradeviation{@required, 21.1} Defining the system frequency using the _XTAL_FREQ macro is required by the XC8 compiler for the built-in delay functions.
*/
/* cppcheck-suppress misra-c2012-21.1 */
#define _XTAL_FREQ 64000000U
#endif

/**
 * @ingroup clockdriver
 * @brief Initializes all the Internal Oscillator sources and the clock switch configurations. 
 * @param None.
 * @return None.
 */
void CLOCK_Initialize(void);

#endif	/* CLOCK_H */
/**
 End of File
*/
