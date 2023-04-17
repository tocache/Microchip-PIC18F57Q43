#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HTINTOSC habilitado
    TRISDbits.TRISD0 = 0;           //RD0 como salida
    ANSELDbits.ANSELD0 = 0;         //RD0 como digital
    T0CON0 = 0x80;                  //Tmr0 ON, postscaler 1:1
    T0CON1 = 0x63;                  //Source HFINTOSC, prescaler 1:8
    TMR0H = 250;                    //Valor de referencia de comparacion
}

void main(void) {
    configuro();
    while(1){
        while(PIR3bits.TMR0IF == 0);
        PIR3bits.TMR0IF = 0;
        LATDbits.LATD0 = ~LATDbits.LATD0;
    }
}
