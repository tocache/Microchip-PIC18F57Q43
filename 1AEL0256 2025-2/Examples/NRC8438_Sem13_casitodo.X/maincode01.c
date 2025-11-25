/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 17 de noviembre de 2025, 05:31 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inicializacion de modulos
    U1_INIT(BAUD_9600);
}

void main(void) {
    configuro();
    while(1){
        U1_STRING_SEND("Hola Mundo!");
        U1_NEWLINE();
        U1_STRING_SEND("Apuren que nos quedamos sin tiempo!");
        U1_NEWLINE();        
        __delay_ms(4000);
    }
}
