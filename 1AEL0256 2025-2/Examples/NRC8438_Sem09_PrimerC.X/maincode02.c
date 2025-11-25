/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 20 de octubre de 2025, 05:48 PM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

const unsigned char tbl_nums_7seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                       0x6D, 0x7D, 0x07, 0x7F, 0x67};

void configuro(void){
    //conf el modulo de oscilador
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;       //RD6 al RD0 son salidas
    ANSELD = 0x80;      //RD6 al RD0 como digitales
    TRISFbits.TRISF1 = 0;   //RF1 como salida
    ANSELFbits.ANSELF1 = 0; //RF1 como digital
    //por defecto los puertos son entradas analógicas
    ANSELBbits.ANSELB2 = 0; //RB2 como digital
    ANSELBbits.ANSELB3 = 0; //RB3 como digital
    WPUBbits.WPUB2 = 1;     //RB2 con pullup
    WPUBbits.WPUB3 = 1;     //RB3 con pullup
    //condicionales de operacion
    LATFbits.LATF1 = 0;
}

void LED_rojo(unsigned char dato){
    if(dato >= 6){
        LATFbits.LATF1 = 1; //LED se enciende cuando es 6
    }
    else{
        LATFbits.LATF1 = 0; //LED se apaga cuando no es 6
    }
}

void main(void) {
    configuro();
    while(1){
        unsigned char x_var;
        for(x_var=0;x_var<10;x_var++){
            LATD = tbl_nums_7seg[x_var];
            LED_rojo(x_var);
            __delay_ms(500);
        }
    }
}
