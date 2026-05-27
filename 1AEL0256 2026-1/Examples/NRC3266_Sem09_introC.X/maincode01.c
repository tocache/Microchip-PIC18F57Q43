/*
 * File:   maincode00.c
 * Author: Alumnos
 *
 * Created on May 27, 2026, 10:04 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 48000000UL

//UL=unsigned long

void configuro(void){
    //conf mod de oscilador
    OSCCON1 = 0x60;     //NOSC=HFINTOSC NDIV 1:1
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;       //RD(6:0) salidas
    ANSELD = 0x80;      //RD(6:0) digitales
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0; //RC0 digital
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup ernabled
}

void main(void) {
    configuro();
    LATD = 0x6D;
    while(1){
        if(PORTBbits.RB0 == 0){
            LATCbits.LATC0 = 1;
            __delay_ms(9);
            LATCbits.LATC0 = 0;
            __delay_ms(1);
        }
        else{
            LATCbits.LATC0 = 1;
            __delay_ms(1);
            LATCbits.LATC0 = 0;
            __delay_ms(9);
        }
    }
}
