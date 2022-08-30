#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL
#define ON 0
#define OFF 1

void configuro(void){
    TRISFbits.TRISF3 = 0;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
}

void main(void) {
    configuro();
    while(1){
        if(PORTBbits.RB4 == ON){
            LATFbits.LATF3 = ON;
            __delay_ms(100);
            LATFbits.LATF3 = OFF;
            __delay_ms(100);            
        }
        else{
            LATFbits.LATF3 = OFF;
        }
    }
}
