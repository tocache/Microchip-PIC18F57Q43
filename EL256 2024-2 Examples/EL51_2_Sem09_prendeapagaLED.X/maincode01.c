/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 9 de octubre de 2024, 05:25 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //config de la fuente de reloj
    OSCCON1 = 0x60;     //HFINTOSC POSTS 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 con pullup
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
}

void main(void) {
    configuro();
    while(1){
        LATBbits.LATB0 = 1; //enciendo LED
        __delay_ms(500);
        LATBbits.LATB0 = 0; //apaga el LED
        __delay_ms(500);
    }
}
