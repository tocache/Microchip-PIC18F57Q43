#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;         //HFINTOSC, POSTS 1:1
    OSCFRQ = 0x07;          //HFINTOSC a 48MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup activado
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
}

void main(void) {
    configuro();
    while(1){
        if(PORTBbits.RB4 == 0){
            LATBbits.LATB0 = 1;
            __delay_ms(100);
            LATBbits.LATB0 = 0;
            __delay_ms(100);
        }
        else{
            LATBbits.LATB0 = 1;
            __delay_ms(300);
            LATBbits.LATB0 = 0;
            __delay_ms(300);
        }
    }
}
