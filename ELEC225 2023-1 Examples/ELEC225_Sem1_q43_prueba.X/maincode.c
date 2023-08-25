#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;     //HFINTOSC con divisor en 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCENbits.HFOEN = 1;    //Habilitacion de HFINTOSC
    TRISD = 0x00;       //todo el RD como salida
    ANSELD = 0x00;      //todo el RD como digital
}

void main(void) {
    configuro();
    while(1){
        LATD = 0xFF;
        __delay_ms(500);
        LATD = 0x00;
        __delay_ms(500);
    }
}
