//Para display de anodo comun

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char texto[] = {0x3E,0x73,0x77,0x3F};

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HTINTOSC habilitado
    TRISB = 0x80;                   //RB6 al RB0 salidas
    ANSELB = 0x80;                  //RB6 al RB0 digitales
    TRISA = 0xF0;                   //RA3 al RA0 salidas
    ANSELA = 0xF0;                  //RA3 al RA0 digitales
    TRISDbits.TRISD0 = 1;           //RD0 entrada
    ANSELDbits.ANSELD0 = 0;         //RD0 digital
    WPUDbits.WPUD0 = 1;             //pull-up en RD0 activada
    LATA = 0xFF;                    //condicion inicial de la multiplexacion
}

void multiplex(void){
    LATB = ~texto[0];
    LATA = ~0xFE;
    __delay_ms(20);
    LATA = 0xFF;
    LATB = ~texto[1];
    LATA = ~0xFD;
    __delay_ms(20);
    LATA = ~0xFF;
    LATB = ~texto[2];
    LATA = ~0xFB;
    __delay_ms(20);
    LATA = ~0xFF;
    LATB = ~texto[3];
    LATA = ~0xF7;
    __delay_ms(20);
    LATA = ~0xFF;
}

void main(void) {
    configuro();
    while(1){
        multiplex();
    }
}
