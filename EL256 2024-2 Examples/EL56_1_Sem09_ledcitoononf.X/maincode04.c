/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 11 de octubre de 2024, 09:35 AM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL
#define RAPIDO 1
#define LENTITO 0

unsigned char ESTADO = LENTITO;
unsigned char SECUENCIA[]={0x00,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01};

void configuro(void){
    //conf la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC POSTS=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 es entrada
    ANSELBbits.ANSELB4 = 0; //RB4 es digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISD = 0;   //RD es salida
    ANSELD = 0; //RD es digital
    //config de la INT2
    INT2PPS = 0x0C;         //asignando RB4 para INT2
    INTCON0bits.INT2EDG = 0;    //falling_edge para INT2
    PIE10bits.INT2IE = 1;   //activo INT2
    INTCON0bits.GIE = 1;    //habilitador global de ints ON
    PIR10bits.INT2IF = 0;   //bajamos bandera INT2
}

void pregunta(void){
    if(ESTADO == RAPIDO){
        __delay_ms(100);
    }
    else if(ESTADO == LENTITO){
        __delay_ms(500);
    }
}

void main(void){
    configuro();
    while(1){
        unsigned char VARX;
        for(VARX=0;VARX<11;VARX++){
            LATD = SECUENCIA[VARX];
            pregunta();
        }
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;   //bajamos bandera de INT2
    if(ESTADO == LENTITO){
        ESTADO = RAPIDO;
    }
    else if(ESTADO == RAPIDO){
        ESTADO = LENTITO;
    }
}
