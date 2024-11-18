/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 13 de noviembre de 2024, 02:35 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char horas=10,minutos=10,segundos=10;

void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60; 
    OSCFRQ = 0x06;
    //OSCEN = 0x40;     HFINTOSC enabled
    OSCEN = 0x48;       //HFINTOSC enabled SOSC enabled
    //configuracion del Timer1
    //T1CLK = 0x01;       //clk source fosc/4
    //T1CON = 0x33;       //TMR1 ON, pres 1:8
    T1CLK = 0x07;         //clk source sosc
    T1CON = 0x03;         //TMR1 ON, presc 1:1
    //configuracion del CCP1
    CCP1CON = 0x81;     //compare mode, clear TMR1
    CCPR1H = 0x80;
    CCPR1L = 0x00;      //valor de referencia 32768
    //configuracion de E/S
    TRISB = 0xFF;       //RB1 RB0 como entradas
    ANSELB = 0xFC;      //RB1 RB0 como digitales
    WPUB = 0x03;        //RB1 RB0 pullup enabled    
    //configuracion de las interrupciones
    INTCON0bits.INT0EDG = 0;    //falling edge en INT0
    INTCON0bits.INT1EDG = 0;    //falling edge en INT1
    PIE1bits.INT0IE = 1;        //INT0 enabled
    PIE6bits.INT1IE = 1;        //INT1 enabled  
    PIR1bits.INT0IF = 0;        //flag INT0 bajada
    PIR6bits.INT1IF = 0;        //flag INT2 bajada    
    PIE3bits.CCP1IE = 1;        //CCP1 enabled
    PIR3bits.CCP1IF = 0;        //flag CCP1 bajada
    INTCON0bits.GIE = 1;        //global ints enabled
    //inicializacion del I2C_LCD
    I2C_LCD_INIT();
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Relojon 2024 :)");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Hecho por Kalun");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    pantallazo();
    I2C_POS_CURSOR(1,2);
    I2C_ESCRIBE_MENSAJE2("Relojon UPC");
    while(1){
        I2C_POS_CURSOR(2,2);
        I2C_LCD_ESCRIBE_VAR_CHAR(horas, 2);
        I2C_ENVIA_LCD_DATA(':');
        I2C_LCD_ESCRIBE_VAR_CHAR(minutos, 2);
        I2C_ENVIA_LCD_DATA(':');
        I2C_LCD_ESCRIBE_VAR_CHAR(segundos, 2);
    }
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;
    if(segundos == 59){
        segundos = 0;
        if(minutos == 59){
            minutos = 0;
            if(horas == 23){
                horas = 0;
            }
            else{
                horas++;
            }
        }
        else{
            minutos++;
        }
    }
    else{
        segundos++;
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(horas == 23){
        horas = 0;
    }
    else{
        horas++;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(minutos == 59){
        minutos = 0;
    }
    else{
        minutos++;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void)
{
// Unhandled interrupts go here
}