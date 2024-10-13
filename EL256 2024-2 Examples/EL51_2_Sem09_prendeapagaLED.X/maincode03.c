/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 9 de octubre de 2024, 05:25 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL
#define E_LENTO 0
#define E_RAPIDO 1

unsigned char estado=E_LENTO;

void configuro(void){
    //config de la fuente de reloj
    OSCCON1 = 0x60;     //HFINTOSC POSTS 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 con pullup
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    //config de la INT1
    INT1PPS = 0x0C;     //RB4 sea la INT1
    INTCON0bits.INT1EDG = 0;    //INT1 en falling-edge
    PIE6bits.INT1IE = 1;    //INT1 enabled
    INTCON0bits.GIE = 1;    //GIE enabled
}

void condicion(void){
        if(estado == E_LENTO){
            __delay_ms(500);
        }
        else{
            __delay_ms(100);
        }
}

void main(void) {
    configuro();
    while(1){
        LATBbits.LATB0 = 1;
        condicion();
        LATBbits.LATB0 = 0;
        condicion();
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;    //bajamos la bandera
    if(estado == E_LENTO){
        estado = E_RAPIDO;
    }
    else{
        estado = E_LENTO;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}
