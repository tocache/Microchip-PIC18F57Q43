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

// get/set RA0 aliases
#define SERVO_TRIS                 TRISAbits.TRISA0
#define SERVO_LAT                  LATAbits.LATA0
#define SERVO_PORT                 PORTAbits.RA0
#define SERVO_WPU                  WPUAbits.WPUA0
#define SERVO_OD                   ODCONAbits.ODCA0
#define SERVO_ANS                  ANSELAbits.ANSELA0
#define SERVO_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SERVO_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SERVO_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SERVO_GetValue()           PORTAbits.RA0
#define SERVO_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SERVO_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SERVO_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define SERVO_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define SERVO_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define SERVO_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define SERVO_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define SERVO_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

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

// get/set RD0 aliases
#define TRIG_TRIS                 TRISDbits.TRISD0
#define TRIG_LAT                  LATDbits.LATD0
#define TRIG_PORT                 PORTDbits.RD0
#define TRIG_WPU                  WPUDbits.WPUD0
#define TRIG_OD                   ODCONDbits.ODCD0
#define TRIG_ANS                  ANSELDbits.ANSELD0
#define TRIG_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define TRIG_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define TRIG_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define TRIG_GetValue()           PORTDbits.RD0
#define TRIG_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define TRIG_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define TRIG_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define TRIG_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define TRIG_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define TRIG_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define TRIG_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define TRIG_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set RD1 aliases
#define ECHO_TRIS                 TRISDbits.TRISD1
#define ECHO_LAT                  LATDbits.LATD1
#define ECHO_PORT                 PORTDbits.RD1
#define ECHO_WPU                  WPUDbits.WPUD1
#define ECHO_OD                   ODCONDbits.ODCD1
#define ECHO_ANS                  ANSELDbits.ANSELD1
#define ECHO_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define ECHO_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define ECHO_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define ECHO_GetValue()           PORTDbits.RD1
#define ECHO_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define ECHO_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define ECHO_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define ECHO_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define ECHO_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define ECHO_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define ECHO_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define ECHO_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RE0 aliases
#define LED_TRIS                 TRISEbits.TRISE0
#define LED_LAT                  LATEbits.LATE0
#define LED_PORT                 PORTEbits.RE0
#define LED_WPU                  WPUEbits.WPUE0
#define LED_OD                   ODCONEbits.ODCE0
#define LED_ANS                  ANSELEbits.ANSELE0
#define LED_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_GetValue()           PORTEbits.RE0
#define LED_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set RF0 aliases
#define TX_TRIS                 TRISFbits.TRISF0
#define TX_LAT                  LATFbits.LATF0
#define TX_PORT                 PORTFbits.RF0
#define TX_WPU                  WPUFbits.WPUF0
#define TX_OD                   ODCONFbits.ODCF0
#define TX_ANS                  ANSELFbits.ANSELF0
#define TX_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define TX_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define TX_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define TX_GetValue()           PORTFbits.RF0
#define TX_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define TX_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define TX_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define TX_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define TX_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define TX_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define TX_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define RX_TRIS                 TRISFbits.TRISF1
#define RX_LAT                  LATFbits.LATF1
#define RX_PORT                 PORTFbits.RF1
#define RX_WPU                  WPUFbits.WPUF1
#define RX_OD                   ODCONFbits.ODCF1
#define RX_ANS                  ANSELFbits.ANSELF1
#define RX_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define RX_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define RX_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define RX_GetValue()           PORTFbits.RF1
#define RX_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define RX_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define RX_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define RX_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define RX_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define RX_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define RX_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

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