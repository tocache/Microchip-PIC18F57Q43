#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 8000000UL

unsigned char mensaje[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x38,
                    0x79, 0x39, 0x78, 0x50, 0x3F, 0x54, 0x06, 0x39, 0x77,
                    0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char indice = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x03;
    OSCEN = 0x40;
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISB = 0xC0;
    ANSELB = 0xC0;
    ANSELE = 0xFC;
    WPUE = 0x03;
    T0CON0 = 0x90;
    T0CON1 = 0x43;
    INTCON0bits.GIE = 1;
    PIE3bits.TMR0IE = 1;
}

void multiplexacion(void){
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

void main(void) {
    configuro();
    while(1){
        multiplexacion();
    }
}

void __interrupt(irq(TMR0)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0;
    if(indice == 16){
        indice = 0;
    }
    else{
        indice++;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}