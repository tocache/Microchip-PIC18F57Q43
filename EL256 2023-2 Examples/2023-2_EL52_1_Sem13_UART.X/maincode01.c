#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;             //HFINTOSC DIV 1:1
    OSCFRQ = 0x06;              //HFINTOSC a 32MHz
    OSCEN = 0x40;               //HFINTOSC enabled
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;       //RA0 entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 analogica
    TRISBbits.TRISB0 = 1;       //RB0 entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 digital
    WPUBbits.WPUB0 = 1;         //RB0 pullup enabled
    TRISBbits.TRISB1 = 1;       //RB1 entrada
    ANSELBbits.ANSELB1 = 0;     //RB1 digital
    WPUBbits.WPUB1 = 1;         //RB1 pullup enabled
    TRISCbits.TRISC0 = 0;       //RC0 salida
    ANSELCbits.ANSELC0 = 0;     //RC0 digital
    TRISCbits.TRISC1 = 0;       //RC1 salida
    ANSELCbits.ANSELC1 = 0;     //RC1 digital
    TRISFbits.TRISF0 = 0;       //RF0 salida
    ANSELFbits.ANSELF0 = 0;     //RF0 digital
    TRISFbits.TRISF1 = 1;       //RF1 entrada
    ANSELFbits.ANSELF1 = 0;     //RF1 digital
    //configuracion del display 16x2
    LCD_INIT();
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("EL52-1 Sem13");
    unsigned char x;
    for(x=0;x<=16;x++){
        POS_CURSOR(2,(16-x));
        ESCRIBE_MENSAJE2("Microcontrolador");
        __delay_ms(300);
    }
    while(1){
        
    }
}
