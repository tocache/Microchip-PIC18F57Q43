/*
 * File:   maincode01.c
 * Author: Kalun Lau
 *
 * Created on 9 de octubre de 2024, 01:22 PM
 * Mi primer ejemplo en XC8 en alto nivel
 */

#include <xc.h>
#include "cabecera.h"

#define _XTAL_FREQ 32000000UL

void configuro(void){
    //config fuente de reloj
    OSCCON1 = 0x60;     //HFINTOSC POSTS 1:1
    OSCFRQ = 0x06;      //HFINTOSC 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISBbits.TRISB0 = 0;   //RB0 salida
    ANSELBbits.ANSELB0 = 0; //RB0 digital
}

void main(void) {
    configuro();
    while(1){
        LATBbits.LATB0 = 1; //enciende el LED
        __delay_ms(250);
        LATBbits.LATB0 = 0; //apaga el LED
        __delay_ms(250);
    }
}
