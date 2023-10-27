#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HTINTOSC habilitado
    TRISBbits.TRISB0 = 0;           //RB0 como salida
    ANSELBbits.ANSELB0 = 0;         //RB0 como digital
    T0CON0 = 0x80;                  //Tmr0 ON, postscaler 1:1
    T0CON1 = 0x41;                  //Source FOSC/4, prescaler 1:2
    TMR0H = 250;                    //Valor de referencia de comparacion
}

void main(void) {
    configuro();                            //llama a función configuro
    while(1){                               //bucle repetitivo
        while(PIR3bits.TMR0IF == 0);        //pregunto si TMR0IF=1
        LATDbits.LATD0 = ~LATDbits.LATD0;   //basculo RB0
        PIR3bits.TMR0IF = 0;                //bajo banderda TMR0IF
    }
}

