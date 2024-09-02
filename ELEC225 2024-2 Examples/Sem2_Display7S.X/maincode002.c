/*
 * File:   maincode001.c
 * Author: Kalun Lau
 *
 * Created on 26 de agosto de 2024, 11:06 AM
 */
//Este es otro comentario

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //Fuente de reloj:
    OSCCON1 = 0x60;         //NOSC:HFINTOSC NDIV: 1/1
    OSCFRQ = 0x02;          //HFINTOSC a 4MHz
    OSCEN = 0x40;           //HFINTOSC habilitado
    //Puertos de E/S:
    TRISB = 0x00;           //RB como salida
    ANSELB = 0x00;          //RB como digitales
    TRISDbits.TRISD0 = 1;   //RD0 como entrada
    ANSELDbits.ANSELD0 = 0; //RD0 como digital
}

void main(void) {
    configuro();
    while(1){
        LATB = 0x3E;        //Letra U
        __delay_ms(500);
        LATB = 0x73;        //Letra P
        __delay_ms(500);
        LATB = 0x77;        //Letra A
        __delay_ms(500);
        LATB = 0x3F;        //Letra O
        __delay_ms(500);
    }
}
