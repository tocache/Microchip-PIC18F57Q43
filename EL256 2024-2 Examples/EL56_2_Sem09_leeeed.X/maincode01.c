/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 11 de octubre de 2024, 03:42 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //config la fuente reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config las E/S
    TRISBbits.TRISB0 = 0;   //RB0 sea salida
    ANSELBbits.ANSELB0 = 0; //RB0 sea digital
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB$ pull-up enabled
}

void pregunto_delay(void){
    if(PORTBbits.RB4 == 0){
        __delay_ms(100);
    }
    else{
        __delay_ms(500);
    }
}

void main(void) {
    configuro();
    while(1){
        LATBbits.LATB0 = 1; //enciendo LED
        pregunto_delay();
        LATBbits.LATB0 = 0; //apagar LED
        pregunto_delay();
    }
}
