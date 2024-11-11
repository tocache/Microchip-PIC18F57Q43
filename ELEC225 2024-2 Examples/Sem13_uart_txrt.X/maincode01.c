/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 11 de noviembre de 2024, 09:35 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configurar las E/S
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    //inicializacion del UART1
    U1_INIT(BAUD_57600);
    //configuracion de las interrupciones
    PIE4bits.U1RXIE = 1;
    PIR4bits.U1RXIF = 0;
    INTCON0bits.GIE = 1;    
}

void vis_menu(void){
    U1_STRING_SEND("*******************************");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("* Bienvenidos a la aplicacion *");
    U1_NEWLINE();
    U1_STRING_SEND("* Desarrollado por Kalun Lau  *");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("*      .--.                   *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |__| .-------.         *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |=.| |.-----.|         *");  
    U1_NEWLINE();
    U1_STRING_SEND("*      |--| || KCK ||         *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |  | |'-----'|         *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |__|~')_____('         *");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("* Elija opcion:               *");
    U1_NEWLINE();
    U1_STRING_SEND("* (1) Enciende el LED en RE0  *");
    U1_NEWLINE();
    U1_STRING_SEND("* (2) Apaga el LED en RE0     *");
    U1_NEWLINE();
    U1_STRING_SEND("* (m) Visualiza el menu       *");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("*******************************");
    U1_NEWLINE();
}

void main(void) {
    configuro();
    __delay_ms(1000);    
    vis_menu();
    while(1){
        
    }
}

//atencion al ingreso desde el teclado
void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    switch(U1RXB){
        case '1':
            LATEbits.LATE0 = 1;
            U1_STRING_SEND("LED encendido!");
            U1_NEWLINE();
            break;
        case '2':
            LATEbits.LATE0 = 0;
            U1_STRING_SEND("LED apagado!");
            U1_NEWLINE();
            break;
        case 'm':
            vis_menu();
            break;
        default:
            U1_STRING_SEND("Opcion invalidad, intente de nuevo");
            U1_NEWLINE();
    }
}
