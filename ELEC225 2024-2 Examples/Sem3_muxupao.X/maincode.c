/*
 * File:   maincode.c
 * Author: upao
 *
 * Created on 2 de septiembre de 2024, 10:34 AM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

#define time 100

void configuro(void){
    //configuracion de la fuente de reloj
    OSCCON1 = 0x60;     //Fuente:HFINTOSC, DIV a 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    // configuracion de las E/S
    TRISD = 0x00;       //RD como salida
    ANSELD = 0x00;      //RD como digital
    TRISB = 0xF0;       //RB[3:0] como salidas
    ANSELB = 0xF0;      //RB[3:0] como digitales
    TRISF = 0xFF;       //RF[1:0] como entradas
    ANSELF = 0xFC;      //RF[0:1] como digitales
    WPUF = 0x03;        //RF[0:1] pullup activadas
    //condicion inicial
    LATB = 0x00;        //RB[3:0]=0x00
}

void multiplexacion(void){
    LATD = 0x3E;        //Letra U
    LATBbits.LATB0 = 1;
    __delay_ms(time);
    LATBbits.LATB0 = 0;
    LATD = 0x73;        //Letra P
    LATBbits.LATB1 = 1;
    __delay_ms(time);
    LATBbits.LATB1 = 0;
    LATD = 0x77;        //Letra A
    LATBbits.LATB2 = 1;
    __delay_ms(time);
    LATBbits.LATB2 = 0;
    LATD = 0x3F;        //Letra O
    LATBbits.LATB3 = 1;
    __delay_ms(time);
    LATBbits.LATB3 = 0;
}

void main(void) {
    configuro();
    while(1){
        multiplexacion();
    }
}
