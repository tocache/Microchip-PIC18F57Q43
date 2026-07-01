/**
 * TMR1 Generated Driver API Header File
 *
 * @file tmr1.h
 *
 * @defgroup tmr1 TMR1
 *
 * @brief This file contains API prototypes and other data types for the TMR1 driver.
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

#ifndef TMR1_H
#define TMR1_H

#include <stdbool.h>
#include <stdint.h>
#include "tmr1_deprecated.h"

/**
 * @misradeviation{@advisory,2.5}
 * MCC Melody drivers provide macros that can be added to an application. 
 * It depends on the application whether a macro is used or not. 
 */
 
/**
 * @ingroup tmr1
 * @brief Defines the maximum count value of the timer.
 */
#define TMR1_MAX_COUNT (65535U)
/**
 * @ingroup tmr1
 * @brief Defines the TMR1 prescaled clock frequency in hertz.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TMR1_CLOCK_FREQ (2000000UL)
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_MAX_COUNT.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TIMER1_MAX_COUNT TMR1_MAX_COUNT
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CLOCK_FREQ.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define TIMER1_CLOCK_FREQ TMR1_CLOCK_FREQ
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_Initialize API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Initialize TMR1_Initialize
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_Deinitialize API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Deinitialize TMR1_Deinitialize
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_Start API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Start TMR1_Start
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_Stop API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Stop TMR1_Stop
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CounterGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_CounterGet TMR1_CounterGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_CounterSet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_CounterSet TMR1_CounterSet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_PeriodSet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_PeriodSet TMR1_PeriodSet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_PeriodGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_PeriodGet TMR1_PeriodGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_MaxCountGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_MaxCountGet TMR1_MaxCountGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_Reload API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Reload TMR1_Reload
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_GateStateGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_GateStateGet TMR1_GateStateGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_SinglePulseAcquisitionStart API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_SinglePulseAcquisitionStart TMR1_SinglePulseAcquisitionStart
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_GateCallbackRegister API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_GateCallbackRegister TMR1_GateCallbackRegister
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_OverflowCallbackRegister API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_OverflowCallbackRegister TMR1_OverflowCallbackRegister
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_GateEventStatusGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_GateEventStatusGet TMR1_GateEventStatusGet

/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_GateEventStatusClear API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_GateEventStatusClear TMR1_GateEventStatusClear
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_OverflowStatusGet API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_OverflowStatusGet TMR1_OverflowStatusGet
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_OverflowStatusClear API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_OverflowStatusClear TMR1_OverflowStatusClear
/**
 * @ingroup tmr1
 * @brief Defines the Custom Name for the \ref TMR1_Tasks API.
 */
/* cppcheck-suppress misra-c2012-2.5 */
#define Timer1_Tasks TMR1_Tasks

/**
 * @ingroup tmr1
 * @brief Initializes the Timer1 (TMR1) module.
 *        This routine must be called before any other TMR1 routines.
 * @param None.
 * @return None.
 */
void TMR1_Initialize(void);

/**
 * @ingroup  tmr1
 * @brief    Deinitializes the TMR1 to POR values.
 * @param    None.
 * @return   None.
 */
void TMR1_Deinitialize(void);

/**
 * @ingroup tmr1
 * @brief Starts the TMR1 timer.
 * @pre Initialize TMR1 with TMR1_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR1_Start(void);

/**
 * @ingroup tmr1
 * @brief Stops the TMR1 timer.
 * @pre Initialize TMR1 with TMR1_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR1_Stop(void);

/**
 * @ingroup tmr1
 * @brief Returns the current counter value.
 * @pre Initialize TMR1 with TMR1_Initialize() before calling this API.
 * @param None.
 * @return Counter value from the TMR1 register
 */
uint16_t TMR1_CounterGet(void);

/**
 * @ingroup tmr1
 * @brief Sets the counter value.
 * @pre Initialize TMR1 with TMR1_Initialize() before calling this API.
 * @param timerVal - Counter value to be written to the TMR1 register
 * @return None.
 */
void TMR1_CounterSet(uint16_t timerVal);

/**
 * @ingroup tmr1
 * @brief Sets the period count value for the TMR1 timer. 
 *        The period count is calculated by subtracting the number of ticks required for the period from the maximum count.
 * @param periodVal - Period value to be stored in the timer period variable
 * @return None.
 */
void TMR1_PeriodSet(uint16_t periodVal);

/**
 * @ingroup tmr1
 * @brief Returns the period count value.
 * @param None.
 * @return Period count value
 */
uint16_t TMR1_PeriodGet(void);

/**
 * @ingroup tmr1
 * @brief Loads the period count value to the TMR1 register.
 * @pre Initialize TMR1 with TMR1_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR1_Reload(void);

/**
 * @ingroup tmr1
 * @brief Returns the TMR1 maximum count value.
 * @param None.
 * @return Maximum count value of the timer
 */
uint16_t TMR1_MaxCountGet(void);

/**
 * @ingroup tmr1
 * @brief Starts the single pulse acquisition in TMR1 gate operation.
 * @pre Use this function only when the TMR1 gate is enabled.
 * @param None.
 * @return None.
 */
void TMR1_SinglePulseAcquisitionStart(void);

/**
 * @ingroup tmr1
 * @brief Returns the TMR1 gate state value.
 * @pre Use this function only when the TMR1 gate is enabled.
 * @param None.
 * @return Gate state value
 */
uint8_t TMR1_GateStateGet(void);

/**
 * @ingroup tmr1
 * @brief Returns the TMR1 Gate flag status in Non-Interrupt mode.
 * @param None.
 * @retval True  - Timer Gate Event has occurred
 * @retval False - Timer Gate Event has not occurred
 */
bool TMR1_GateEventStatusGet(void);

/**
 * @ingroup tmr1
 * @brief Clears the TMR1 Gate flag in Non-Interrupt mode.
 * @param None.
 * @return None. 
 */
void TMR1_GateEventStatusClear(void);

/**
 * @ingroup tmr1
 * @brief Returns the TMR1 overflow flag status in Non-Interrupt mode.
 * @param None.
 * @retval True  - Timer overflow has occurred
 * @retval False - Timer overflow has not occurred
 */
bool TMR1_OverflowStatusGet(void);

/**
 * @ingroup tmr1
 * @brief Clears the TMR1 overflow flag in Non-Interrupt mode .
 * @param None.
 * @return None. 
 */
void TMR1_OverflowStatusClear(void);

/**
 * @ingroup tmr1
 * @brief Performs the tasks to be executed during the TMR1 overflow or gate event.
 * @param None.
 * @return None.
 */
void TMR1_Tasks(void);

/**
 * @ingroup tmr1
 * @brief Registers a callback function for the TMR1 overflow event.
 * @param CallbackHandler - Address of the custom callback function
 * @return None.
 */
 void TMR1_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr1
 * @brief Registers a callback function for the TMR1 gate event.
 * @param CallbackHandler - Address of the custom callback function
 * @return None.
 */
 void TMR1_GateCallbackRegister(void (* CallbackHandler)(void));

#endif // TMR1_H