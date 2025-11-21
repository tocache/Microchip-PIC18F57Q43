/*
 * File:   maincoide01.c
 * Author: Alumnos
 *
 * Created on 24 de octubre de 2025, 04:23 PM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //conf modulo de oscilador
    OSCCON1 = 0x60; //NOSC HFINTOSC NDIV 1:1
    OSCFRQ = 0x02;  //HFINTOSC a 4MHz
    OSCEN = 0x40;   //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;   //RD(6:0) salidas
    ANSELD = 0x80;  //RD(6:0) digitales
    TRISFbits.TRISF1 = 0;   //RF1 salida
    ANSELFbits.ANSELF1 = 0; //RF1 digital
    TRISEbits.TRISE0 = 0;   //RE0 salida
    ANSELEbits.ANSELE0 = 0; //RE0 digital
    ANSELB = 0xE3;          //RB2 RB3 RB4 digitales
    WPUBbits.WPUB2 = 1;     //RB2 pullup enabled
}

void main(void) {
    configuro();
    while(1){
        LATEbits.LATE0 = 1; //LED on
        __delay_ms(300);
        LATEbits.LATE0 = 0; //LED off
        __delay_ms(300);
    }
}
