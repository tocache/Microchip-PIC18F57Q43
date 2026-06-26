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

unsigned char anime[]={0x21, 0x03, 0x42, 0x50,
                        0x18, 0x0C, 0x44, 0x60};

void main(void) {
    configuro();
    LATCbits.LATC0 = 1;
    while(1){
        for(unsigned char xvar=0;xvar<8;xvar++){
            if(PORTBbits.RB0 == 0){
                LATD = anime[xvar];
            }
            else{
                LATD = anime[7-xvar];
            }
            __delay_ms(100);
        }
    }
}
