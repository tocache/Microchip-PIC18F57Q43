/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 10 de octubre de 2024, 06:33 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL
#define RAPIDO 1
#define LENTO 0

unsigned char ESTADO = LENTO;

void configuro(void){
    //config la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC POSTS=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    //config la INT1
    INT1PPS = 0x0C;     //asignar INT1 hacia RB4
    INTCON0bits.INT1EDG = 0;    //INT1 en falling_edge
    PIE6bits.INT1IE = 1;        //INT1 enabled
    INTCON0bits.GIE = 1;        //interrupciones habilitadas
    PIR6bits.INT1IF = 0;        //bajamos bandera de INT1
}

void pregunta(void){
    if(ESTADO == LENTO){
        __delay_ms(500);
    }
    else if(ESTADO == RAPIDO){
        __delay_ms(100);
    }
}

void main(void) {
    configuro();
    while(1){
        LATBbits.LATB0 = 1; //enciende el LED
        pregunta();
        LATBbits.LATB0 = 0; //apago el LED
        pregunta();
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;    //bajamos bandera INT1
    if(ESTADO == LENTO){
        ESTADO = RAPIDO;
    }
    else if(ESTADO == RAPIDO){
        ESTADO = LENTO;
    }
}
