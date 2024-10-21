/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 14 de octubre de 2024, 10:45 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

//variables globales
unsigned char horas = 11;
unsigned char minutos = 50;
unsigned char segundos = 0;
unsigned char ticks = 0;

void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;       //HFINTOSC a 32Mhz
    //conf del Timer1 y del CCP1
    T1CLK = 0x01;
    T1CON = 0x33;
    CCP1CON = 0x81;     //modo comparador con rst a TMR1
    CCPR1H = 0xF4;
    CCPR1L = 0x24;      //valor de ref de comp 62500
    //conf de la interrupcion
    PIE3bits.CCP1IE = 1;    //habilito CCP1IE
    INTCON0bits.GIE = 1;    //habilitador global de ints
    PIR3bits.CCP1IF = 0;
    //conf del LCD
    I2C_LCD_INIT();
    __delay_ms(100);
}

void main(void) {
    configuro();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Reloj UPAO");
        I2C_POS_CURSOR(2,0);
        I2C_LCD_ESCRIBE_VAR_CHAR(horas,2);
        I2C_ENVIA_LCD_DATA(':');
        I2C_LCD_ESCRIBE_VAR_CHAR(minutos,2);
        I2C_ENVIA_LCD_DATA(':');
        I2C_LCD_ESCRIBE_VAR_CHAR(segundos,2);
    }
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;
    if(ticks == 15){
        ticks = 0;
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
    else{
        ticks++;
    }
}

void __interrupt(irq(default)) default_ISR(void){
    
}
