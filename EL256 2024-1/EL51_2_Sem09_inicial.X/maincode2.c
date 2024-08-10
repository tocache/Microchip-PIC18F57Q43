#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    OSCCON1 = 0x60;     //NOSC=HFINTOSC NDIV=1:1
    OSCFRQ = 0x07;      //HFINTOSC=48MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    ANSELFbits.ANSELF3 = 0; //RF3 digital
    TRISFbits.TRISF3 = 0;   //RF3 output
}

void main(void) {
    configuro();
    LCD_INIT();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo!");
    while(1){
        LATFbits.LATF3 = 0; //LED on
        __delay_ms(300);
        LATFbits.LATF3 = 1; //LED off
        __delay_ms(300);        
    }
}

