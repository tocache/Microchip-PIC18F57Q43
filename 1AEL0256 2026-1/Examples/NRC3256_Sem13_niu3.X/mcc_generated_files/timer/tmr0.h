/**
 * TMR0 Generated Driver API Header File
 * 
 * @file tmr0.h
 * 
 * @defgroup tmr08bit TMR0 in 8-Bit Mode
 * 
 * @brief This file contains API prototypes and other data types for the TMR0 driver.
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

#ifndef TMR0_H
#define TMR0_H

#include <stdint.h>
#include <stdbool.h>
#include "tmr0_deprecated.h"

/**
 * @misradeviation{@advisory,2.5}
 * MCC Melody drivers provide macros that can be added to an application. 
 * It depends on the application whether a macro is used or not. 
 */
 
/**
 * @ingroup tmr08bit
 * @brief Defines the maximum count value of the timer.
 */
#define TMR0_MAX_COUNT (255U)
/**
 * @ingroup tmr08bit
 * @brief Defines the timer prescaled clock frequency in hertz.
 */
/* cppcheck-suppress misra-c2012-2.5 */ 
#define TMR0_CLOCK_FREQ (64000000UL)
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_MAX_COUNT.
 */
/* cppcheck-suppress misra-c2012-2.5 */ 
#define TIMER0_MAX_COUNT TMR0_MAX_COUNT
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CLOCK_FREQ.
 */
/* cppcheck-suppress misra-c2012-2.5 */ 
#define TIMER0_CLOCK_FREQ TMR0_CLOCK_FREQ
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_Initialize API.
 */
/* cppcheck-suppress misra-c2012-2.5 */ 
#define Timer0_Initialize TMR0_Initialize
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_Deinitialize API.
 */
/* cppcheck-suppress misra-c2012-2.5 */ 
#define Timer0_Deinitialize TMR0_Deinitialize
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_Start API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_Start TMR0_Start
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_Stop API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_Stop TMR0_Stop
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CounterGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_CounterGet TMR0_CounterGet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_CounterSet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_CounterSet TMR0_CounterSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodSet API
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_PeriodSet TMR0_PeriodSet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_PeriodGet TMR0_PeriodGet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_MaxCountGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_MaxCountGet TMR0_MaxCountGet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodMatchStatusGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_PeriodMatchStatusGet TMR0_PeriodMatchStatusGet
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodMatchStatusClear API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_PeriodMatchStatusClear TMR0_PeriodMatchStatusClear
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_PeriodMatchCallbackRegister API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_PeriodMatchCallbackRegister TMR0_PeriodMatchCallbackRegister
/**
 * @ingroup tmr08bit
 * @brief Defines the Custom Name for the \ref TMR0_Tasks API.
 */
/* cppcheck-suppress misra-c2012-2.5 */  
#define Timer0_Tasks TMR0_Tasks

/**
 * @ingroup tmr08bit
 * @brief Initializes the Timer0 (TMR0) module.
 *        This routine must be called before any other TMR0 routines.
 * @param None.
 * @return None.
 */
void TMR0_Initialize(void);

/**
 * @ingroup tmr08bit
 * @brief Deinitializes the TMR0 module.
 * @param None.
 * @return None.
 */
void TMR0_Deinitialize(void);

/**
 * @ingroup tmr08bit
 * @brief Starts the TMR0 timer.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR0_Start(void);

/**
 * @ingroup tmr08bit
 * @brief Stops the TMR0 timer.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR0_Stop(void);

/**
 * @ingroup tmr08bit
 * @brief Returns the current counter value.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return Counter value from the TMR0L register
 */
uint8_t TMR0_CounterGet(void);

/**
 * @ingroup tmr08bit
 * @brief Sets the counter value.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param counterValue - Counter value to be written to the TMR0L register
 * @return None.
 */
void TMR0_CounterSet(uint8_t counterValue);

/**
 * @ingroup tmr08bit
 * @brief Sets the period value.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param periodCount - Period count value written to the TMR0H register
 * @return None.
 */
void TMR0_PeriodSet(uint8_t periodCount);

/**
 * @ingroup tmr08bit
 * @brief Returns the current period value.
 * @pre Initialize TMR0 with TMR0_Initialize() before calling this API.
 * @param None.
 * @return Period count value from the TMR0H register
 */
uint8_t TMR0_PeriodGet(void);

/**
 * @ingroup tmr08bit
 * @brief Returns the maximum count value.
 * @param None.
 * @return Maximum count value
 */
uint8_t TMR0_MaxCountGet(void);

/**
 * @ingroup tmr08bit
 * @brief Returns the status of the TMR0 interrupt flag.
 * @param None.
 * @return Interrupt flag status
 */
bool TMR0_PeriodMatchStatusGet(void);

/**
 * @ingroup tmr08bit
 * @brief Clears the TMR0 interrupt flag.
 * @param None.
 * @return None.
 */
void TMR0_PeriodMatchStatusClear(void);

/**
 * @ingroup tmr08bit
 * @brief Performs tasks to be executed during the timer interrupt event.
 * @param None.
 * @return None.
 */
void TMR0_Tasks(void);

/**
 * @ingroup tmr08bit
 * @brief Registers a callback function for the TMR0 overflow or period match event.
 * @param CallbackHandler - Address to the custom callback function
 * @return None.
 */
void TMR0_PeriodMatchCallbackRegister(void (* CallbackHandler)(void));

#endif //TMR0_H