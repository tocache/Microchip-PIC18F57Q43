/**
 * System Driver Header File
 * 
 * @file system.h
 * 
 * @defgroup systemdriver System Driver
 * 
 * @brief This file contains the API prototype for the System Driver.
 *
 * @version Driver Version 2.0.3
 *
 * @version Package Version 5.3.5
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

#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../system/config_bits.h"
#include "../system/pins.h"
#include "../uart/uart1.h"
#include "../system/interrupt.h"
#include "../system/clock.h"
#include "../adc/adc.h"
#include "../i2c_host/i2c1.h"
#include "../timer/tmr0.h"

/**
 * @ingroup systemdriver
 * @brief Initializes the system module.
 * This routine is called only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
*/
void SYSTEM_Initialize(void);

#endif	/* SYSTEM_H */
/**
 End of File
*/