#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL        //Frecuencia de trabajo

unsigned char tabla[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};
unsigned char cuenta = 0;

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HTINTOSC habilitado
    TRISBbits.TRISB4 = 1;           //RB4 entrada
    ANSELBbits.ANSELB4 = 0;         //RB4 digital
    WPUBbits.WPUB4 = 1;             //Weak pullup en RB4 habilitada
    TRISD = 0x80;                   //RD6 al RD0 como salidas
    ANSELD = 0x80;                  //RD6 al RD0 como digitales
}

void main(void) {
    configuro();
    while(1){
        LATD = tabla[cuenta];
        __delay_ms(500);
        if(PORTBbits.RB4 == 0){
            cuenta = 0;
        }
        else{
            if(cuenta == 9){
                cuenta = 0;
            }
            else{
                cuenta++;
            }
        }
    }
}