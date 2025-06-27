/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 29 de mayo de 2025, 07:02 PM
 */
//This is a comment, you must use // before each comment or /**/ for multi-line
//comments

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISD = 0x80;
    ANSELD = 0x80;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB0 = 0;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
}

unsigned char mensaje[]={0x71, 0x77, 0x30, 0x38, 0x6D, 0x77, 0x6D, 0x3F};

void main(void) {
    configuro();
    while(1){
        unsigned char x_var;
        for(x_var=0;x_var<8;x_var++){
            LATD = mensaje[x_var];
            __delay_ms(500);
        }
    }
}
