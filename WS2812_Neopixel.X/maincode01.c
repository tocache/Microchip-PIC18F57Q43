/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 29 de septiembre de 2024, 09:23 PM
 */

#include <xc.h>
#include "cabecera.h"

#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
}

void main(void) {
    configuro();
    while(1){
        LATFbits.LATF3 = 0;
        __delay_ms(500);
        LATFbits.LATF3 = 1;
        __delay_ms(500);
    }
}
