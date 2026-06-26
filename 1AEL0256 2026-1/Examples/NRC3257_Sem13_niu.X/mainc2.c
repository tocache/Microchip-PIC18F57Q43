 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

void UART1_String_Write(const char *cadenon){
    while(*cadenon){
        UART1_Write(*cadenon++);
    }
}

void UART1_NewLine(void){
        UART1_Write(0x0A);
        UART1_Write(0x0D);
}

int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global High Interrupts 
    //INTERRUPT_GlobalInterruptHighEnable(); 

    // Disable the Global High Interrupts 
    //INTERRUPT_GlobalInterruptHighDisable(); 

    // Enable the Global Low Interrupts 
    //INTERRUPT_GlobalInterruptLowEnable(); 

    // Disable the Global Low Interrupts 
    //INTERRUPT_GlobalInterruptLowDisable(); 

    while(1){
        UART1_String_Write("********************************");
        UART1_NewLine();
        UART1_String_Write("*                              *");
        UART1_NewLine();
        UART1_String_Write("*   Microcontroladores 2026-1  *");
        UART1_NewLine();
        UART1_String_Write("*        UPC Monterrico        *");
        UART1_NewLine();
        UART1_String_Write("     Profesor Kalun Lau Gan    *");
        UART1_NewLine();
        UART1_String_Write("*                              *");
        UART1_NewLine();
        if(UART1_IsRxReady()){
            switch(UART1_Read()){
                case 'r':
                    IO_RE0_SetHigh();
                    UART1_String_Write("*     LED RE0 encendido        *");
                    UART1_NewLine();
                    break;
                case 't':
                    IO_RE1_SetHigh();
                    UART1_String_Write("*     LED RE1 encendido        *");
                    UART1_NewLine();
                    break;
                case 'b':
                    IO_RE0_SetLow();
                    UART1_String_Write("*     LED RE0 apagado          *");
                    UART1_NewLine();
                    break;
                case 'n':
                    IO_RE1_SetLow();
                    UART1_String_Write("*     LED RE1 apagado          *");
                    UART1_NewLine();
                    break;
                default:
                    UART1_String_Write("*     OPCION INVALIDA          *");
                    UART1_NewLine();
            }
        }
        if(IO_RB0_GetValue()){
            UART1_String_Write("*     BTN0 sin presionar       *");
            UART1_NewLine();
        }
        else{
            UART1_String_Write("*     BTN0 presionado          *");
            UART1_NewLine();
        }
        if(IO_RB1_GetValue()){
            UART1_String_Write("*     BTN1 sin presionar       *");
            UART1_NewLine();
        }
        else{
            UART1_String_Write("*     BTN1 presionado          *");
            UART1_NewLine();
        }        
        UART1_String_Write("********************************");
        UART1_NewLine();
        __delay_ms(500);
    }    
}