/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 24 de octubre de 2025, 10:19 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //conf el modulo de oscilador}
    OSCCON1 = 0x60; //NOSC HFINTOSC NDIV 1:1
    OSCFRQ = 0x02;  //HFINTOSC 4MHz
    OSCEN = 0x40;   //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;   //RD(6:0) salidas
    ANSELD = 0x80;  //RD(6:0) digitales
    TRISEbits.TRISE0 = 0;   //RE0 salida
    ANSELEbits.ANSELE0 = 0; //RE0 digital
    TRISFbits.TRISF0 = 0;   //RF0 salida
    ANSELFbits.ANSELF0 = 0; //RF0 digital
    ANSELB = 0xC7;  //RB3, RB4, RB5 digitales
    WPUBbits.WPUB5 = 1; //RB5 pullup enabled
}

void main(void) {
    configuro();
    while(1){
        //prueba 1: prender un apagar los LEDs
        /*LATEbits.LATE0 = 1;
        LATFbits.LATF0 = 0;
        __delay_ms(500);
        LATFbits.LATF0 = 1;
        LATEbits.LATE0 = 0;
        __delay_ms(500);*/
        //prueba 2: probar los sensores
        if(PORTBbits.RB3 == 1){     //sensor Hall
            LATEbits.LATE0 = 1;
        }
        else{
            LATEbits.LATE0 = 0;
        }
        if(PORTBbits.RB4 == 0){     //sensor LDR
            LATFbits.LATF0 = 1;
        }
        else{
            LATFbits.LATF0 = 0;
        }
        
    }
}
