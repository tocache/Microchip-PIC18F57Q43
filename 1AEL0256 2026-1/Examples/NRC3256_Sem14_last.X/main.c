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
#include "LIB_DHT.h"

/*
    Main application
*/

float HCSR04_GetDistance(void){
    //condiciones inicial
    Timer0_CounterSet(0x0000);
    //envio del pulso de 10us por TRIG
    IO_RF2_SetHigh();
    __delay_us(10);
    IO_RF2_SetLow();
    //medir el tiempo del ancho positivo de la señal de ECHO
    while(!IO_RF3_GetValue());
    Timer0_Start();
    while(IO_RF3_GetValue());
    Timer0_Stop();
    return (Timer0_CounterGet() / 58.31);
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
        UART1_String_Write("Hola mundo, prueba de envio de variables al terminal serial");
        UART1_NewLine();
        UART1_String_Write("Variable 8bit:");
        UART1_8bitVar_Write(124);
        UART1_NewLine();
        UART1_String_Write("Variable 16bit:");
        UART1_16bitVar_Write(35353);
        UART1_NewLine();
        UART1_String_Write("Variable float:");
        UART1_Float_Write(353.456,2);
        UART1_NewLine();
        UART1_String_Write("Distancia HCSR04:");
        UART1_Float_Write(HCSR04_GetDistance(),4);
        UART1_String_Write(" cm");        
        UART1_NewLine();
        UART1_String_Write("Temperatura DHT11:");
        UART1_16bitVar_Write2(DHT_GetTemp(DHT11),4);
        UART1_String_Write(" °C");        
        UART1_NewLine();
        __delay_ms(2000);
        UART1_String_Write("Humedad DHT11:");
        UART1_16bitVar_Write2(DHT_GetHumid(DHT11),4);
        UART1_String_Write(" %RH");        
        UART1_NewLine();        
        __delay_ms(2000);
    }    
}