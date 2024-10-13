/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 11 de octubre de 2024, 09:35 AM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC POSTS=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 es entrada
    ANSELBbits.ANSELB4 = 0; //RB4 es digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISBbits.TRISB0 = 0;   //RB0 es salida
    ANSELBbits.ANSELB0 = 0; //RB0 es digital
}

void main(void) {
    configuro();
    while(1){
        if(PORTBbits.RB4 == 0){
            LATBbits.LATB0 = 1; //enciendo el LED
            __delay_ms(100);
            LATBbits.LATB0 = 0; //apagado el LED
            __delay_ms(100);
        }
        else if(PORTBbits.RB4 == 1){
            LATBbits.LATB0 = 1; //enciendo el LED
            __delay_ms(500);
            LATBbits.LATB0 = 0; //apagado el LED
            __delay_ms(500);
        }
    }
}
