#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion del reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup activado
}

void main(void){
    configuro();
    while(1){
        if(PORTBbits.RB4 == 0){
            //parpadeo rapido
            LATBbits.LATB0 = 1;     //enciendo LED
            __delay_ms(100);
            LATBbits.LATB0 = 0;     //apago LED
            __delay_ms(100);
        }
        else{
            //parpadeo lento
            LATBbits.LATB0 = 1;     //enciendo LED
            __delay_ms(200);
            LATBbits.LATB0 = 0;     //apago LED
            __delay_ms(200);
        }
    }
}

