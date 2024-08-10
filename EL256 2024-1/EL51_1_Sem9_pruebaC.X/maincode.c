#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 48000000UL

void configuro(){
    OSCCON1 = 0x60;         //NOSC=HFINTOSC NDIV1:1
    OSCFRQ = 0x07;          //HFINTOSC 48MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    TRISFbits.TRISF3 = 0;   //RF3 output
    ANSELFbits.ANSELF3 = 0; //RF3 digital
}

void main(void) {
    configuro();            //calling configuro function
    while(1){               //do it forever
        LATFbits.LATF3 = 0; //LED on
        __delay_ms(200);    //delay of 200ms
        LATFbits.LATF3 = 1; //LED off
        __delay_ms(200);    //delay of 200ms
    }
}
