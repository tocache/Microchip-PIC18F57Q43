//Este es un comentario
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char dato = 0; //para almacenar temporalmente
                        //el valor ingresado
unsigned char tabla[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

void configuro(void){
    OSCCON1 = 0x60;     //HFINTOSC y 1:1
    OSCFRQ = 0x02;      //HFINTOSC trabajando a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    TRISD = 0x80;       //RD6 al RD0 como salidas
    ANSELD = 0x80;      //RD6 al RD0 como digitales
    TRISB = 0xFF;       //RB3 al RB0 como entradas
    ANSELB = 0xF0;      //RB3 al RB0 como digitales
}

void main(void){
    configuro();
    while(1){
        dato = PORTB & 0x0F;    //lectura de RB y enmascaramiento para RB3-RB0
        LATD = tabla[dato];     //tabla de búsqueda y escritura en RD6-RD0
    }
}