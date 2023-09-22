//Este es un comentario
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char dato = 0; //para almacenar temporalmente
                        //el valor ingresado
unsigned char mensaje[] = {0x76, 0x3F, 0x38, 0x77};

void configuro(void){
    OSCCON1 = 0x60;     //HFINTOSC y 1:1
    OSCFRQ = 0x02;      //HFINTOSC trabajando a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    TRISD = 0x80;       //RD6 al RD0 como salidas
    ANSELD = 0x80;      //RD6 al RD0 como digitales
    TRISB = 0xF0;       //RB3 al RB0 como salidas
    ANSELB = 0xF0;      //RB3 al RB0 como digitales
    LATB = 0x00;        //Inicialmente RB todos en cero (digitos del display deshabilitados)
}

void main(void){
    configuro();
    while(1){
        LATD = mensaje[0];
        LATBbits.LATB0 = 1;
        __delay_ms(1);
        LATBbits.LATB0 = 0;
        LATD = mensaje[1];
        LATBbits.LATB1 = 1;
        __delay_ms(1);
        LATBbits.LATB1 = 0;
        LATD = mensaje[2];
        LATBbits.LATB2 = 1;
        __delay_ms(1);
        LATBbits.LATB2 = 0;
        LATD = mensaje[3];
        LATBbits.LATB3 = 1;
        __delay_ms(1);
        LATBbits.LATB3 = 0;
    }
}