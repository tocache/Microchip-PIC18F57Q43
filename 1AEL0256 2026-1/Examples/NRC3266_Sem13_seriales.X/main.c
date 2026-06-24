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
#include <string.h>

/*
    Main application
*/

void UART1_String_Write(const char *cadena)
{
	unsigned char i = 0, tam = 0;
    tam = strlen(cadena);
	for(i = 0; i<tam; i++)
	{
        UART1_Write(cadena[i]);
        while(!UART1_IsTxDone());
	}
}

void UART1_NewLine(void){
    UART1_Write(0x0A);
    while(!UART1_IsTxDone());
    UART1_Write(0x0D);
    while(!UART1_IsTxDone());
}

int main(void){
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
    unsigned char angulo = 0;
    while(1)
    {
        /*IO_RE0_LAT = 1;
        __delay_ms(500);
        IO_RE0_LAT = 0;
        __delay_ms(500);*/
        UART1_String_Write("Hola mundo!");
        UART1_String_Write("UPC San Miguelino");
        UART1_NewLine();
        __delay_ms(1000);
        while(UART1_IsRxReady()){
            switch(UART1_Read()){
                case 'w':
                    IO_RE1_LAT = 1;
                    UART1_String_Write("LED RE1 encendido");
                    UART1_NewLine();
                    break;
                case 'm':
                    IO_RE1_LAT = 0;
                    UART1_String_Write("LED RE1 apagado");
                    UART1_NewLine();
                    break;
                case 'x':
                    angulo = 0;
                    UART1_String_Write("Servo a 0 grados");
                    UART1_NewLine();
                    break;
                case 'c':
                    angulo = 1;
                    UART1_String_Write("Servo a 90 grados");
                    UART1_NewLine();
                    break;
                case 'v':
                    angulo = 2;
                    UART1_String_Write("Servo a 180 grados");
                    UART1_NewLine();
                    break;
            }
        }
        switch(angulo){
            case 0:
                IO_RE2_LAT = 1;
                __delay_us(2500);
                IO_RE2_LAT = 0;
                __delay_us(17500);
                break;
            case 1:
                IO_RE2_LAT = 1;
                __delay_us(1500);
                IO_RE2_LAT = 0;
                __delay_us(18500);
                break;
            case 0:
                IO_RE2_LAT = 1;
                __delay_us(500);
                IO_RE2_LAT = 0;
                __delay_us(19500);
                break;
        }
    }    
}