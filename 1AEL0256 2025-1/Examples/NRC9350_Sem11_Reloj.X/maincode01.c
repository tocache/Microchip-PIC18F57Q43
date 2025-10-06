/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 9 de junio de 2025, 06:03 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCENbits.HFOEN = 1;
    //conf de las E/S
    //conf del CCP2 y TMR2
    RF0PPS = 0x16;      //CCP2 sale por RF0
    T2PR = 98;          //TMR2 a 5KHz (200us)
    CCP2CON = 0x9C;     //CCP2 Enabled, PWM just izq
    CCPR2H = 49;        //Duty Cycle a 50%
    CCPR2L = 0;
    T2CLKCON = 0x01;    //TMR2 src FOSC/4
    T2CON = 0xC0;       //TMR2 enabled, PSC 1:16
    TRISFbits.TRISF0 = 0;   //RF0 salida
    ANSELFbits.ANSELF0 = 0; //RF0 digital
    //conf del ADC
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogico
    ADCON0bits.ADFM = 0;    //just izquierda
    ADCON0bits.CS = 1;       //ADC src ADCRC
    ADPCH = 0x00;           //RA0 va a leerse
    ADCON0bits.ADON = 1;    //ADC enabled
}

void main(void) {
    configuro();
    while(1){
        ADCON0bits.GO_nDONE = 1;    //toma una muestra ADC
        while(ADCON0bits.GO_nDONE == 1);    //espera a que termine
        CCPR2H = ADRESH;
    }
}
