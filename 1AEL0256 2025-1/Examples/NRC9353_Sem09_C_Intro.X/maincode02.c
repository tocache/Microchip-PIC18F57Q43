/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 29 de mayo de 2025, 03:03 PM
 */
//Este es un comentario, mi segundo ejemplo con el XC8 de alto nivel para el
//Curiosity Nano PIC18F57Q43
//Hecho por Kalun Lau 29/05/2025

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;     //NOSC HFINTOSC, NDIV 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISD = 0x80;       //RD(6:0) como salidas
    ANSELD = 0x80;      //RD(6:0) como digitales
    TRISBbits.TRISB0 = 1;   //RB0 como entrada
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    WPUBbits.WPUB0 = 1;     //RB0 con pullup habilitado
    TRISBbits.TRISB1 = 1;   //RB1 como entrada
    ANSELBbits.ANSELB1 = 0; //RB1 como digital
    WPUBbits.WPUB1 = 1;     //RB1 con pullup habilitado
    //configuracion de las interrupciones INT0 e INT1
    INT0PPS = 0x08;         //INT0 asignado a RB0
    INT1PPS = 0x09;         //INT1 asignado a RB1
    PIE1bits.INT0IE = 1;    //INT0 enabled
    PIE6bits.INT1IE = 1;    //INT1 enabled
    INTCON0bits.INT0EDG = 0;    //INT0 flanco negativo
    INTCON0bits.INT1EDG = 0;    //INT1 flanco negativo
    INTCON0bits.GIE = 1;        //GIE habilitado
}

void main(void) {
    configuro();
    while(1);
}

//zona de las funciones de interrupcion
void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;        //bajamos la bandera INT0IF
    LATD = 0x77;
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;        //bajamos la bandera INT1IF
    LATD = 0x00;
}
