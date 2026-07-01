/**
 * TMR1 Generated Driver API Header File
 *
 * @file tmr1.h
 *
 * @defgroup tmr1 TMR1
 *
 * @brief This file contains the deprecated macros or APIs for the TMR1 driver.
 *
 * @version TMR1 Driver Version 4.1.1
 * 
 * @version Package Version 5.2.2
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

#ifndef TMR1_DEPRECATED_H
#define TMR1_DEPRECATED_H

#warning "The tmr1_deprecated.h file contains the deprecated macros or functions. Replace the deprecated macro or functions with the recommended alternative."

/**
 * @misradeviation{@advisory,2.5}
 * MCC Melody drivers provide macros that can be added to an application. 
 * It depends on the application whether a macro is used or not. 
 */
 
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CounterGet API.
 *        The TMR1_Read will be deprecated in the future release. Use TMR1_CounterGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_Read TMR1_CounterGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CounterGet API.
 *        The Timer1_Read will be deprecated in the future release. Use Timer1_CounterGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Read TMR1_CounterGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CounterSet API.
 *        The TMR1_Write will be deprecated in the future release. Use TMR1_CounterSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_Write TMR1_CounterSet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CounterSet API.
 *        The Timer1_Write will be deprecated in the future release. Use Timer1_CounterSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Write TMR1_CounterSet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_PeriodSet API.
 *        The TMR1_PeriodCountSet will be deprecated in the future release. Use TMR1_PeriodSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_PeriodCountSet TMR1_PeriodSet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_PeriodSet API.
 *        The Timer1_PeriodCountSet will be deprecated in the future release. Use Timer1_PeriodSet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_PeriodCountSet TMR1_PeriodSet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_GateStateGet API.
 *        The TMR1_CheckGateValueStatus will be deprecated in the future release. Use TMR1_GateStateGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_CheckGateValueStatus TMR1_GateStateGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_GateStateGet API.
 *        The Timer1_CheckGateValueStatus will be deprecated in the future release. Use Timer1_GateStateGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_CheckGateValueStatus TMR1_GateStateGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_SinglePulseAcquisitionStart API.
 *        The TMR1_StartSinglePulseAcquisition will be deprecated in the future release. Use TMR1_SinglePulseAcquisitionStart instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_StartSinglePulseAcquisition TMR1_SinglePulseAcquisitionStart
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_SinglePulseAcquisitionStart API.
 *        The Timer1_StartSinglePulseAcquisition will be deprecated in the future release. Use Timer1_SinglePulseAcquisitionStart instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_StartSinglePulseAcquisition TMR1_SinglePulseAcquisitionStart
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_OverflowStatusGet API.
 *        The TMR1_HasOverflowOccured will be deprecated in the future release. Use TMR1_OverflowStatusGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_HasOverflowOccured TMR1_OverflowStatusGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_OverflowStatusGet API.
 *        The Timer1_HasOverflowOccured will be deprecated in the future release. Use Timer1_OverflowStatusGet instead.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_HasOverflowOccured TMR1_OverflowStatusGet

#endif // TMR1_DEPRECATED_H