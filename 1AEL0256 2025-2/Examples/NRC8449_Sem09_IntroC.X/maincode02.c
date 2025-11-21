/*
 * File:   maincoide01.c
 * Author: Alumnos
 *
 * Created on 24 de octubre de 2025, 04:23 PM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

const unsigned char gusanito[] = {0x01, 0x02, 0x40, 0x10,
                                0x08, 0x04, 0x40, 0x20};

void configuro(void){
    //conf modulo de oscilador
    OSCCON1 = 0x60; //NOSC HFINTOSC NDIV 1:1
    OSCFRQ = 0x02;  //HFINTOSC a 4MHz
    OSCEN = 0x40;   //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;   //RD(6:0) salidas
    ANSELD = 0x80;  //RD(6:0) digitales
    TRISFbits.TRISF1 = 0;   //RF1 salida
    ANSELFbits.ANSELF1 = 0; //RF1 digital
    TRISEbits.TRISE0 = 0;   //RE0 salida
    ANSELEbits.ANSELE0 = 0; //RE0 digital
    ANSELB = 0xE3;          //RB2 RB3 RB4 digitales
    WPUBbits.WPUB2 = 1;     //RB2 pullup enabled
    //condiciones iniciales
    LATFbits.LATF1 = 1;     //habilito display7s
}

void anima_gusanito_r(unsigned char veces){
    unsigned char x_var, y_var;
    for(y_var=0;y_var<veces;y_var++){
        for(x_var=0;x_var<8;x_var++){
            LATD = gusanito[x_var];
            __delay_ms(50);
        }
    }
}

void anima_gusanito_l(unsigned char veces){
    unsigned char x_var, y_var;
    for(y_var=0;y_var<veces;y_var++){
        for(x_var=0;x_var<8;x_var++){
            LATD = gusanito[7-x_var];
            __delay_ms(50);
        }
    }
}

void main(void) {
    configuro();
    anima_gusanito_r(4);
    anima_gusanito_l(4);
    while(1){
        LATEbits.LATE0 = 1; //LED on
        __delay_ms(300);
        LATEbits.LATE0 = 0; //LED off
        __delay_ms(300);
    }
}
