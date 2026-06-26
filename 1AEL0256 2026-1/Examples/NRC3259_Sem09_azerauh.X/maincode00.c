/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on May 29, 2026, 10:19 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 64000000UL

void configuro(void){
    //conf del mod de osc
    OSCCON1 = 0x60;
    OSCFRQ = 0x08;
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
        LATD = 0x5B;
    }
}
