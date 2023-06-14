#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISE = 0xF8;
    ANSELE = 0xF8;
    TRISD = 0x0F;
    ANSELD = 0x0F;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    //El boton en RB4 que sea la INT1
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    INTCON0bits.INT1EDG = 0;
    INT1PPS = 0x0C;             //remapeado INT1 hacia RB4
    INTCON0bits.GIE = 1;        //habilitador global de interrupciones activado
    PIE6bits.INT1IE = 1;        //habilitador de INT1 activao
    LCD_INIT();
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola Mundo!");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Micro semana 13");
    __delay_ms(4000);
    BORRAR_LCD();
}


void main(void) {
    configuro();
    pantallazo();
    while(1){
        
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    pantallazo();
}