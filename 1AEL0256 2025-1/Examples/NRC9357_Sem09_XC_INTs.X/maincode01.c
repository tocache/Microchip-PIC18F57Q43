/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 30 de mayo de 2025, 09:57 AM
 */
//Este es un comentario, programa para hacer un contador con limites
//Hecho por Kalun 30/05/2025

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISD = 0x80;       //RD6 al RD0 como salidas
    ANSELD = 0x80;      //RD6 al RD0 como digitales
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB0 = 0;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    //configuracion de las INT0 e INT1
    INT0PPS = 0x08;         //INT0 asignado a RB0
    INT1PPS = 0x09;         //INT1 asignado a RB1
    PIE1bits.INT0IE = 1;    //INT0 enabled
    PIE6bits.INT1IE = 1;    //INT1 enabled
    PIR1bits.INT0IF = 0;    //INT0 flag down
    PIR6bits.INT1IF = 1;    //INT1 flag down
    INTCON0bits.INT0EDG = 0;    //INT0 falling edge detect
    INTCON0bits.INT1EDG = 0;    //INT1 falling edge detect
    INTCON0bits.GIE = 1;        //Global interrupt enabled
}

const unsigned char tableta[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 
                               0x6D, 0x7D, 0x07, 0x7F, 0x67};
unsigned char numero = 0;

void main(void) {
    configuro();
    while(1){
        LATD = tableta[numero];
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(numero == 0){
        numero = 0;
    }
    else{
        numero--;
    }
    __delay_ms(50);
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(numero == 9){
        numero = 9;
    }
    else{
        numero++;
    }
    __delay_ms(50);    
}