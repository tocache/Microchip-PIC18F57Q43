/**
 * TMR0 Generated Driver API Header File
 * 
 * @file tmr0.h
 * 
 * @defgroup tmr08bit TMR0 in 8-Bit Mode
 * 
 * @brief This file contains the deprecated macros or APIs for the TMR0 driver.
 *
 * @version TMR0 Driver Version 3.0.1
 *
 * @version Package Version 5.1.2
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

#ifndef TMR0_DEPRECATED_H
#define TMR0_DEPRECATED_H

#include <stdint.h>
#include <stdbool.h>

#warning "The tmr0_deprecated.h file contains the deprecated macros or functions. Replace the deprecated macro or functions with the recommended alternative."

/**
 * @misradeviation{@advisory,2.5}
 * MCC Melody drivers provide macros that can be added to an application. 
 * It depends on the application whether a macro is used or not. 
 */
 
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CounterGet API. 
 *        The TMR0_Read will be deprecated in the future release. Use TMR0_CounterGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define TMR0_Read TMR0_CounterGet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CounterGet API. 
 *        The Timer0_Read will be deprecated in the future release. Use TMR0_CounterGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_Read TMR0_CounterGet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CounterSet API.
 *        The TMR0_Write will be deprecated in the future release. Use TMR0_CounterSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define TMR0_Write TMR0_CounterSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CounterSet API.
 *        The Timer0_Write will be deprecated in the future release. Use TMR0_CounterSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_Write TMR0_CounterSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodSet API.
 *        The TMR0_PeriodCountSet will be deprecated in the future release. Use TMR0_PeriodSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define TMR0_PeriodCountSet TMR0_PeriodSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodSet API.
 *        The Timer0_PeriodCountSet will be deprecated in the future release. Use TMR0_PeriodSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_PeriodCountSet TMR0_PeriodSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodSet API.
 *        The TMR0_Reload will be deprecated in the future release. Use TMR0_PeriodSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define TMR0_Reload TMR0_PeriodSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodSet API.
 *        The Timer0_Reload will be deprecated in the future release. Use TMR0_PeriodSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_Reload TMR0_PeriodSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodMatchCallbackRegister API.
 *        The TMR0_OverflowCallbackRegister will be deprecated in the future release. Use TMR0_PeriodMatchCallbackRegister instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define TMR0_OverflowCallbackRegister TMR0_PeriodMatchCallbackRegister
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodMatchCallbackRegister API.
 *        The Timer0_OverflowCallbackRegister will be deprecated in the future release. Use TMR0_PeriodMatchCallbackRegister instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_OverflowCallbackRegister TMR0_PeriodMatchCallbackRegister
/**
 * @}
 */
#endif //TMR0_DEPRECATED_H