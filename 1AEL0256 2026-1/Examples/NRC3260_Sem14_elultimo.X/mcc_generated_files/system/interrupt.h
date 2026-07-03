/**
 * Interrupt Manager Generated Driver API Header File.
 * 
 * @file interrupt.h
 * 
 * @defgroup interrupt INTERRUPT
 * 
 * @brief This file contains API prototypes and the other data types for the Interrupt Manager driver.
 *
 * @version Interrupt Manager Driver Version 2.1.3
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

#ifndef INTERRUPT_H
#define INTERRUPT_H

/**
 * @ingroup interrupt
 * @def INTERRUPT_GlobalInterruptHighEnable()
 * @brief Enables the high priority global interrupts.
 */
#define INTERRUPT_GlobalInterruptHighEnable() (INTCON0bits.GIE = 1)

/**
 * @ingroup interrupt
 * @def INTERRUPT_GlobalInterruptHighDisable()
 * @brief Disables the high priority global interrupts.
 */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCON0bits.GIE = 0)

/**
 * @ingroup interrupt
 * @def INTERRUPT_GlobalInterruptHighStatus()
 * @brief Returns the Global Interrupt Enable bit status.
 * @param None.
 * @retval True - High priority global interrupt is enabled.
 * @retval False - High priority global interrupt is disabled.
 */
#define INTERRUPT_GlobalInterruptHighStatus() (INTCON0bits.GIE)

/**
 * @ingroup interrupt
 * @def INTERRUPT_GlobalInterruptLowEnable()
 * @brief Enables the low priority global interrupts.
 */
#define INTERRUPT_GlobalInterruptLowEnable() (INTCON0bits.GIEL = 1)

/**
 * @ingroup interrupt
 * @def INTERRUPT_GlobalInterruptLowDisable()
 * @brief Disables the low priority global interrupts.
 */
#define INTERRUPT_GlobalInterruptLowDisable() (INTCON0bits.GIEL = 0)

/**
 * @ingroup interrupt
 * @def INTERRUPT_GlobalInterruptLowStatus()
 * @brief Returns the Global Low-Priority Interrupt Enable bit status.
 * @param None.
 * @retval True - Low priority global interrupt is enabled.
 * @retval False - Low priority global interrupt is disabled.
 */
#define INTERRUPT_GlobalInterruptLowStatus() (INTCON0bits.GIEL)

/**
 * @ingroup interrupt
 * @brief Initializes the interrupt controller.
 * @param None.
 * @return None.
 */
void INTERRUPT_Initialize (void);


/**
 * @ingroup interrupt
 * @def Clears the interrupt flag for the external interrupt, INT0.
 * @param None.
 * @return None.
 */
#define EXT_INT0_InterruptFlagClear()       (PIR1bits.INT0IF = 0)

/**
 * @ingroup interrupt
 * @def Disables the external interrupt on the INT0 pin.
 * @param None.
 * @return None.
 */
#define EXT_INT0_InterruptDisable()     (PIE1bits.INT0IE = 0)

/**
 * @ingroup interrupt
 * @def Enables the external interrupt on the INT0 pin.
 * @param None.
 * @return None.
 */
#define EXT_INT0_InterruptEnable()       (PIE1bits.INT0IE = 1)


/**
 * @ingroup interrupt
 * @def Sets the external interrupt to trigger when the pin's level transitions from low to high (positive edge trigger).
 * @param None.
 * @return None.
 */
#define EXT_INT0_risingEdgeSet()          (INTCON0bits.INT0EDG = 1)

/**
 * @ingroup interrupt
 * @brief Sets the external interrupt to trigger when the pin's level transitions from high to low (negative edge trigger).
 * @param None.
 * @return None.
 */
#define EXT_INT0_fallingEdgeSet()          (INTCON0bits.INT0EDG = 0)

/**
 * @ingroup interrupt
 * @def Clears the interrupt flag for the external interrupt, INT1.
 * @param None.
 * @return None.
 */
#define EXT_INT1_InterruptFlagClear()       (PIR6bits.INT1IF = 0)

/**
 * @ingroup interrupt
 * @def Disables the external interrupt on the INT1 pin.
 * @param None.
 * @return None.
 */
#define EXT_INT1_InterruptDisable()     (PIE6bits.INT1IE = 0)

/**
 * @ingroup interrupt
 * @def Enables the external interrupt on the INT1 pin.
 * @param None.
 * @return None.
 */
#define EXT_INT1_InterruptEnable()       (PIE6bits.INT1IE = 1)


/**
 * @ingroup interrupt
 * @def Sets the external interrupt to trigger when the pin's level transitions from low to high (positive edge trigger).
 * @param None.
 * @return None.
 */
#define EXT_INT1_risingEdgeSet()          (INTCON0bits.INT1EDG = 1)

/**
 * @ingroup interrupt
 * @brief Sets the external interrupt to trigger when the pin's level transitions from high to low (negative edge trigger).
 * @param None.
 * @return None.
 */
#define EXT_INT1_fallingEdgeSet()          (INTCON0bits.INT1EDG = 0)

/**
 * @ingroup interrupt
 * @def Clears the interrupt flag for the external interrupt, INT2.
 * @param None.
 * @return None.
 */
#define EXT_INT2_InterruptFlagClear()       (PIR10bits.INT2IF = 0)

/**
 * @ingroup interrupt
 * @def Disables the external interrupt on the INT2 pin.
 * @param None.
 * @return None.
 */
#define EXT_INT2_InterruptDisable()     (PIE10bits.INT2IE = 0)

/**
 * @ingroup interrupt
 * @def Enables the external interrupt on the INT2 pin.
 * @param None.
 * @return None.
 */
#define EXT_INT2_InterruptEnable()       (PIE10bits.INT2IE = 1)


/**
 * @ingroup interrupt
 * @def Sets the external interrupt to trigger when the pin's level transitions from low to high (positive edge trigger).
 * @param None.
 * @return None.
 */
#define EXT_INT2_risingEdgeSet()          (INTCON0bits.INT2EDG = 1)

/**
 * @ingroup interrupt
 * @brief Sets the external interrupt to trigger when the pin's level transitions from high to low (negative edge trigger).
 * @param None.
 * @return None.
 */
#define EXT_INT2_fallingEdgeSet()          (INTCON0bits.INT2EDG = 0)

/**
   Section: External Interrupt Handlers
 */

/**
 * @ingroup interrupt
 * @brief Function to be called in the INT0 ISR containing the interrupt handler function for the INT0 pin interrupt event.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void INT0_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Assigns an interrupt handler for the EXT_INT0 - INT0 interrupt event.
 * @pre INTERRUPT_Initialize() is already called.
 * @param (*InterruptHandler)(void) - Pointer to the InterruptHandler function.
 * @return None.
 */
void INT0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief Function pointer to the interrupt handler for the INT0 pin interrupt event.
 *        This can be reassigned using the INT0_SetInterruptHandler function.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
extern void (*INT0_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief Default interrupt handler assigned to handle INT0 interrupt events.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void INT0_DefaultInterruptHandler(void);

/**
 * @ingroup interrupt
 * @brief Function to be called in the INT1 ISR containing the interrupt handler function for the INT1 pin interrupt event.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void INT1_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Assigns an interrupt handler for the EXT_INT1 - INT1 interrupt event.
 * @pre INTERRUPT_Initialize() is already called.
 * @param (*InterruptHandler)(void) - Pointer to the InterruptHandler function.
 * @return None.
 */
void INT1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief Function pointer to the interrupt handler for the INT1 pin interrupt event.
 *        This can be reassigned using the INT1_SetInterruptHandler function.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
extern void (*INT1_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief Default interrupt handler assigned to handle INT1 interrupt events.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void INT1_DefaultInterruptHandler(void);

/**
 * @ingroup interrupt
 * @brief Function to be called in the INT2 ISR containing the interrupt handler function for the INT2 pin interrupt event.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void INT2_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Assigns an interrupt handler for the EXT_INT2 - INT2 interrupt event.
 * @pre INTERRUPT_Initialize() is already called.
 * @param (*InterruptHandler)(void) - Pointer to the InterruptHandler function.
 * @return None.
 */
void INT2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief Function pointer to the interrupt handler for the INT2 pin interrupt event.
 *        This can be reassigned using the INT2_SetInterruptHandler function.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
extern void (*INT2_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief Default interrupt handler assigned to handle INT2 interrupt events.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void INT2_DefaultInterruptHandler(void);

#endif  // INTERRUPT_H
/**
 End of File
*/
