/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 29 de mayo de 2025, 03:03 PM
 */
//Este es un comentario, mi primer ejemplo con el XC8 de alto nivel para el
//Curiosity Nano PIC18F57Q43
//Hecho por Kalun Lau 29/05/2025

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;     //NOSC HFINTOSC, NDIV 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISD = 0x80;       //RD(6:0) como salidas
    ANSELD = 0x80;      //RD(6:0) como digitales
    TRISBbits.TRISB0 = 1;   //RB0 como entrada
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    WPUBbits.WPUB0 = 1;     //RB0 con pullup habilitado
    TRISBbits.TRISB1 = 1;   //RB1 como entrada
    ANSELBbits.ANSELB1 = 0; //RB1 como digital
    WPUBbits.WPUB1 = 1;     //RB1 con pullup habilitado
}

void main(void) {
    configuro();
//    LATDbits.LATD3 = 0;
    while(1){
        LATD = 0x77;
        __delay_ms(500);
        LATD = 0x00;
        __delay_ms(500);
//        LATDbits.LATD0 = 1;
//        LATDbits.LATD1 = 1;
//        LATDbits.LATD2 = 1;
//        LATDbits.LATD4 = 1;
//        LATDbits.LATD5 = 1;
//        LATDbits.LATD6 = 1;
//        __delay_ms(500);
//        LATDbits.LATD0 = 0;
//        LATDbits.LATD1 = 0;
//        LATDbits.LATD2 = 0;
//        LATDbits.LATD4 = 0;
//        LATDbits.LATD5 = 0;
//        LATDbits.LATD6 = 0;
//        __delay_ms(500);
    }
}
