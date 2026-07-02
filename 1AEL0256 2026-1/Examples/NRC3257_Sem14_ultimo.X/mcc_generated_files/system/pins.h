/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RB1 aliases
#define BOTON_TRIS                 TRISBbits.TRISB1
#define BOTON_LAT                  LATBbits.LATB1
#define BOTON_PORT                 PORTBbits.RB1
#define BOTON_WPU                  WPUBbits.WPUB1
#define BOTON_OD                   ODCONBbits.ODCB1
#define BOTON_ANS                  ANSELBbits.ANSELB1
#define BOTON_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define BOTON_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define BOTON_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define BOTON_GetValue()           PORTBbits.RB1
#define BOTON_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define BOTON_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define BOTON_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define BOTON_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define BOTON_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define BOTON_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define BOTON_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define BOTON_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RF0 aliases
#define IO_RF0_TRIS                 TRISFbits.TRISF0
#define IO_RF0_LAT                  LATFbits.LATF0
#define IO_RF0_PORT                 PORTFbits.RF0
#define IO_RF0_WPU                  WPUFbits.WPUF0
#define IO_RF0_OD                   ODCONFbits.ODCF0
#define IO_RF0_ANS                  ANSELFbits.ANSELF0
#define IO_RF0_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define IO_RF0_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define IO_RF0_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define IO_RF0_GetValue()           PORTFbits.RF0
#define IO_RF0_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define IO_RF0_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define IO_RF0_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define IO_RF0_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define IO_RF0_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define IO_RF0_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define IO_RF0_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define IO_RF0_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define IO_RF1_TRIS                 TRISFbits.TRISF1
#define IO_RF1_LAT                  LATFbits.LATF1
#define IO_RF1_PORT                 PORTFbits.RF1
#define IO_RF1_WPU                  WPUFbits.WPUF1
#define IO_RF1_OD                   ODCONFbits.ODCF1
#define IO_RF1_ANS                  ANSELFbits.ANSELF1
#define IO_RF1_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define IO_RF1_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define IO_RF1_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define IO_RF1_GetValue()           PORTFbits.RF1
#define IO_RF1_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define IO_RF1_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define IO_RF1_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define IO_RF1_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define IO_RF1_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define IO_RF1_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define IO_RF1_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define IO_RF1_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

// get/set RF2 aliases
#define TRIG_TRIS                 TRISFbits.TRISF2
#define TRIG_LAT                  LATFbits.LATF2
#define TRIG_PORT                 PORTFbits.RF2
#define TRIG_WPU                  WPUFbits.WPUF2
#define TRIG_OD                   ODCONFbits.ODCF2
#define TRIG_ANS                  ANSELFbits.ANSELF2
#define TRIG_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define TRIG_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define TRIG_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define TRIG_GetValue()           PORTFbits.RF2
#define TRIG_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define TRIG_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define TRIG_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define TRIG_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define TRIG_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define TRIG_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define TRIG_SetAnalogMode()      do { ANSELFbits.ANSELF2 = 1; } while(0)
#define TRIG_SetDigitalMode()     do { ANSELFbits.ANSELF2 = 0; } while(0)

// get/set RF3 aliases
#define ECHO_TRIS                 TRISFbits.TRISF3
#define ECHO_LAT                  LATFbits.LATF3
#define ECHO_PORT                 PORTFbits.RF3
#define ECHO_WPU                  WPUFbits.WPUF3
#define ECHO_OD                   ODCONFbits.ODCF3
#define ECHO_ANS                  ANSELFbits.ANSELF3
#define ECHO_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define ECHO_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define ECHO_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define ECHO_GetValue()           PORTFbits.RF3
#define ECHO_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define ECHO_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define ECHO_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define ECHO_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define ECHO_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define ECHO_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define ECHO_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define ECHO_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/