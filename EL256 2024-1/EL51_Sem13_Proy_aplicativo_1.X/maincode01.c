/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 12 de junio de 2024, 02:04 PM
 */
#include <xc.h>
#include "cabcezota.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion del UART
    U1BRGH = 0;
    U1BRGL = 207;           //UART1 a 9600 baudios
    U1CON0 = 0x30;          //TX enabled, RX enabled
    U1CON1 = 0x80;          //UART1 habilitado (enabled)
    U1CON2 = 0x00;          //Dejarlo valores por defecto
    RF0PPS = 0x20;          //RF0 esta conectado a UART1TX
    U1RXPPS = 0x29;         //RF1 esta conectado a UART1RX    
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void U1_NEWLINE(void){
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

void main(void) {
    configuro();
    while(1){
        U1_BYTE_SEND('H');
        U1_BYTE_SEND('o');
        U1_BYTE_SEND('l');
        U1_BYTE_SEND('a'); 
        U1_NEWLINE();
        __delay_ms(1000);
    }
}
