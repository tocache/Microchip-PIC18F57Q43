/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 9 de junio de 2025, 02:08 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuraciuon de las E/S
    //configuración del PWM con el CCP2
    TRISFbits.TRISF0 = 0;   //RF0 como salida
    ANSELFbits.ANSELF0 = 0; //RF0 como digital
    RF0PPS = 0x16;      //señal de PWM del CCP2 sale por RF0
    T2PR = 98;          //Periodo de PWM a 5KHz
    CCP2CON = 0x9C;      //CCP2 ON, just izquierda, PWM mode
    CCPR2H = 49;
    CCPR2L = 0;         //duty cycle a 50%
    T2CLKCON = 0x01;    //TMR2 con FOSC/4
    T2CON = 0xC0;       //TMR2 ON, PSC 1:16
    //configuracion del ADC
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogica
    ADCON0bits.ADFM = 0;          //ADC just izquierda
    ADCON0bits.CS = 1;          //ADCRC como fuente de reloj
    ADPCH = 0x00;               //canal de lectura RA0
    ADCON0bits.ON = 1;          //ADC enabled
    //configuracion de las INTs
}

void main(void) {
    configuro();
    while(1){
        ADCON0bits.GO = 1;      //inicie la toma de una muestra en el ADC
        while(ADCON0bits.GO == 1);  //esperar a que termine de convertir
        CCPR2H = ADRESH;
        __delay_ms(50);
    }
}
