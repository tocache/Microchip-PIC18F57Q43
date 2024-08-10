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
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    TRISBbits.TRISB4 = 1;   //RB4 input
    WPUBbits.WPUB4 = 1;     //RB4 weak pullup enabled
}

void main(void) {
    configuro();
    LCD_INIT();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo!");
    while(1){
        if(PORTBbits.RB4 == 0){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("BTN: pulsado    ");
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("BTN: no pulsado!");
        }
    }
}

