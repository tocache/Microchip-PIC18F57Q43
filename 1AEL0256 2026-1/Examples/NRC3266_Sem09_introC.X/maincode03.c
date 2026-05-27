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

const unsigned char tablota[]={0x01, 0x22, 0x40, 0x14, 0x08};

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
    LATCbits.LATC0 = 1;
    while(1){
        for(unsigned char x_var=0;x_var<5;x_var++){
            LATD = tablota[x_var];
            if(PORTBbits.RB0 == 0){
                __delay_ms(100);
            }
            else{
                __delay_ms(300);
            }
        }
    }
}
