/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 10 de octubre de 2024, 06:33 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //config la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC POSTS=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
}

void main(void) {
    configuro();
    while(1){
        if(PORTBbits.RB4 == 0){
            //aqui cuando es verdadero
            LATBbits.LATB0 = 1; //enciende el LED
            __delay_ms(100);
            LATBbits.LATB0 = 0; //apago el LED
            __delay_ms(100);
        }
        else{
            //aqui cuando es falso
            LATBbits.LATB0 = 1; //enciende el LED
            __delay_ms(500);
            LATBbits.LATB0 = 0; //apago el LED
            __delay_ms(500);
        }
    }
}
