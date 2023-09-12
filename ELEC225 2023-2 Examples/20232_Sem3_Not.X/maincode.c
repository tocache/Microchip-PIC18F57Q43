//Programa hecho por Kalun
//Realizado el 11/09/2023

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;     //para escoger el HFINTOSC y 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;      //HFINTOSC habilitado
    TRISFbits.TRISF3 = 0;       //RF3 salida
    ANSELFbits.ANSELF3 = 0;     //RF3 digital
    TRISBbits.TRISB4 = 1;       //RB4 entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 digital
    WPUBbits.WPUB4 = 1;         //RB4 pullup activado
}

void main(void){
    configuro();
    while(1){
        if(PORTBbits.RB4 == 0){
            LATFbits.LATF3 = 1;     //Verdad, RF3=1
        }
        else{
            LATFbits.LATF3 = 0;    //Falso, RF3=0
        }
    }
}

