/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on May 28, 2026, 7:58 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 64000000UL

void configuro(void){
    //conf el modulo de oscilador
    OSCCON1 = 0x60;     //NOSC=HFINTOSC NDIV=1:1
    OSCFRQ = 0x08;      //HFINTOSC a 64MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;       //RD6 al RD0 como salidas
    ANSELD = 0x80;      //RD6 al RD0 como digitales
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0; //RC0 digital
}

void main(void) {
    configuro();
    while(1){
        LATCbits.LATC0 = 1;
        LATD = 0x73;
    }
}
