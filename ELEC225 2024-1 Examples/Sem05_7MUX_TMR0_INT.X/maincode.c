#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char mensaje[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x38,
                    0x3E, 0x15, 0x3F, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char indice = 0;

void configuro(void){
    OSCCON1 = 0x60;         //HFINTOSC, DIV 1:1
    OSCFRQ = 0x02;          //HFINTOSC a 4MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    TRISD = 0x00;           //RD outputs
    ANSELD = 0x00;          //RD digital
    TRISB = 0xC0;           //RB5:RB0 outputs
    ANSELB = 0xC0;          //RB5:RB0 digital
    ANSELE = 0xFC;          //RE1:RE0 digital
    WPUE = 0x03;            //RE1:RE0 weak pullup enabled
    T0CON0 = 0x97;          //TMR0 enabled, 16 bits mode, 1:8 postscaler
    T0CON1 = 0x40;          //FOSC/4 clock src, 1:1 prescaler
    PIE3bits.TMR0IE = 1;    //TMR0 interrupt enabled
    INTCON0bits.GIE = 1;    //Global interrupt enabled
    LATB = 0;               //condicion inicial
}

void main(void) {
    configuro();
    while(1){
        LATD = mensaje[indice];
        LATBbits.LATB0 = 1;
        __delay_ms(2);
        LATBbits.LATB0 = 0;
        LATD = mensaje[indice+1];
        LATBbits.LATB1 = 1;
        __delay_ms(2);
        LATBbits.LATB1 = 0;
        LATD = mensaje[indice+2];
        LATBbits.LATB2 = 1;
        __delay_ms(2);
        LATBbits.LATB2 = 0;
        LATD = mensaje[indice+3];
        LATBbits.LATB3 = 1;
        __delay_ms(2);
        LATBbits.LATB3 = 0;
        LATD = mensaje[indice+4];
        LATBbits.LATB4 = 1;
        __delay_ms(2);
        LATBbits.LATB4 = 0;
        LATD = mensaje[indice+5];
        LATBbits.LATB5 = 1;
        __delay_ms(2);
        LATBbits.LATB5 = 0;
    }
}

void __interrupt(irq(IRQ_TMR0)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0;
    if(indice == 11){
        indice = 0;
    }
    else{
        indice++;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}
