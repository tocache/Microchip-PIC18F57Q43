/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on May 28, 2026, 7:58 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 64000000UL

unsigned char secuencia[]={0x09,0x12,0x40,0x24};

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
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup enabled
}

void main(void) {
    configuro();
    LATCbits.LATC0 = 1;
    while(1){
        for(unsigned char x_var=0;x_var<4;x_var++){
            if(PORTBbits.RB0 == 0){
                LATD = secuencia[x_var];
            }
            else{
                LATD = secuencia[3-x_var];
            }   
            __delay_ms(200);
        }
    }
}