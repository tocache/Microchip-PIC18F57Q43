/*
 * File:   maincode.c
 * Author: upao
 *
 * Created on 7 de octubre de 2024, 11:21 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char cuenta = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    TRISE = 0xFC;
    ANSELE = 0xFC;
    WPUE = 0x03;
    TRISB = 0x80;
    ANSELB = 0x80;
    LCD_Init();
}

void visualizacion(void){
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Cuenta:");
    LCD_ESCRIBE_VAR_CHAR(cuenta,3);
}

void siete_seg(void){
    if(cuenta>127){
        LATB = 0x38;
    }
    else{
        LATB = 0x76;
    }
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("TP ELEC-MECA");
    while(1){
        if(PORTEbits.RE0 == 0){
            if(cuenta == 255){
                cuenta = 0;
            }
            else{
                cuenta++;
            }
            visualizacion();
            siete_seg();
            while(PORTEbits.RE0 == 1);
        }
        if(PORTEbits.RE1 == 0){
            if(cuenta == 0){
                cuenta = 255;
            }
            else{
                cuenta--;
            }
            visualizacion();
            siete_seg();
            while(PORTEbits.RE1 == 1);
        }
    }
}
