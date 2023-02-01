#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;     //CPU recibe 4MHz
    TRISFbits.TRISF3 = 0;   //RF3 como salida
}

void main(void){
    configuro();
    while(1){
        LATFbits.LATF3 = 1;
        __delay_ms(100);
        LATFbits.LATF3 = 0;
        __delay_ms(100);
    }
}
