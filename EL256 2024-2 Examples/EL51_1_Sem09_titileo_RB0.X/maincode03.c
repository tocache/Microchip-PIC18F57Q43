/*
 * File:   maincode03.c
 * Author: Kalun Lau
 *
 * Created on 9 de octubre de 2024, 01:22 PM
 * Mi primer ejemplo en XC8 en alto nivel
 */

#include <xc.h>
#include "cabecera.h"

#define _XTAL_FREQ 32000000UL
#define LENTO 0
#define RAPIDO 1

unsigned char estado = LENTO;   //variable que contiene el estado

void configuro(void){
    //config fuente de reloj
    OSCCON1 = 0x60;     //HFINTOSC POSTS 1:1
    OSCFRQ = 0x06;      //HFINTOSC 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISBbits.TRISB0 = 0;   //RB0 salida
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    //config de la INT0
    INT0PPS = 0x0C;         //la INT0 entra por RB4
    INTCON0bits.INT0EDG = 0;    //deteccion activo en bajo de la INT0
    PIE1bits.INT0IE = 1;    //habilitamos INT0
    INTCON0bits.GIE = 1;    //encendemos interrupciones
}

//Sistema del RB4 en modo latch con interrupciones
void main(void) {
    configuro();
    while(1){
        if(estado == RAPIDO){
            LATBbits.LATB0 = 1; //enciende el LED
            __delay_ms(100);
            LATBbits.LATB0 = 0; //apaga el LED
            __delay_ms(100);
        }
        else{
            LATBbits.LATB0 = 1; //enciende el LED
            __delay_ms(300);
            LATBbits.LATB0 = 0; //apaga el LED
            __delay_ms(300);
        }
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;    //bajamos bandera de INT0
    if(estado == LENTO){
        estado = RAPIDO;
    }
    else{
        estado = LENTO;
    }
}

