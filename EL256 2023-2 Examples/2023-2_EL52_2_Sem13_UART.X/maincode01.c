#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB1 = 1;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    TRISFbits.TRISF1 = 1;
    ANSELFbits.ANSELF1 = 0;
    //configuracion del LCD
    LCD_INIT();
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("EL52-2 Semana 13");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2(" uC PIC18F57Q43");
    while(1){
        LATC = 0x01;
        __delay_ms(1000);
        LATC = 0x02;
        __delay_ms(1000);
    }
}
