#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
}

void main(void) {
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
