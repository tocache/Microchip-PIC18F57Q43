/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 10 de octubre de 2024, 02:47 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL
#define RAPIDISIMO 1
#define LENTISIMO 0

unsigned char ESTADO = LENTISIMO;
unsigned char SECUENCIA[]={0x07, 0x0E, 0x1C, 0x38, 0x70, 0xE0, 0x70, 0x38, 0x1C, 0x0E};

void configuro(void){
    //config de la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC POSTS 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISD = 0;   //RD como salida
    ANSELD = 0; //RD como digital
    //config de la INT1
    INT1PPS = 0x0C;     //Asignando RB4 para INT1
    INTCON0bits.INT1EDG = 0;    //INT1 en flanco negativo
    PIE6bits.INT1IE = 1;    //habilitando INT1
    INTCON0bits.GIE = 1;    //habilitador GIE en uno
    PIR6bits.INT1IF = 0;    //bajamos la bandera inicialmente
}

void main(void){
    configuro();
    while(1){
        unsigned char var_x;
        for(var_x=0;var_x<10;var_x++){
            LATD = SECUENCIA[var_x];
            if(ESTADO == LENTISIMO){
                __delay_ms(500);
            }
            else if(ESTADO == RAPIDISIMO){
                __delay_ms(100);
            }
        }
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;    //bajamos la bandera de INT1
    if(ESTADO == RAPIDISIMO){
        ESTADO = LENTISIMO;
    }
    else{
        ESTADO = RAPIDISIMO;
    }
}