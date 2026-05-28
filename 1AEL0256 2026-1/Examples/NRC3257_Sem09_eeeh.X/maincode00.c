/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on May 28, 2026, 11:54 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //conf el mod de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;
    OSCEN = 0x40;
    //conf las E/S
    TRISD = 0x80;
    ANSELD = 0x80;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    ANSELB = 0xFC;
    WPUB = 0x03;
}

void main(void) {
    configuro();
    LATCbits.LATC0 = 1;
    while(1){
        LATD = 0x77;
    }
}
