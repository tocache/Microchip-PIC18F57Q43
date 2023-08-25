#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define __XTAL_FREQ 4000000UL

unsigned char diezmillar,millar,centena,decena,unidad;
unsigned char estado = 0;

void configuro(void){
    //configuracion del reloj principal
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISCbits.TRISC2 = 0;
    ANSELCbits.ANSELC2 = 0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    TRISFbits.TRISF1 = 1;
    ANSELFbits.ANSELF1 = 0;
    TRISB = 0xFF;
    ANSELB = 0xEF;
    WPUBbits.WPUB4 = 1;
    //configuracion del CCP para PWM
    T2PR = 62;              //frecuencia de PWM a 4KHz
    RC2PPS = 0x15;          //PPS asignación de RC2 hacia CCP1
    CCP1CON = 0x9C;         //CCP1 ON, justificacion izquierda, PWM mode
    CCPR1H = 31;
    CCPR1L = 0;             //duty cycle a 50%
    T2CLKCON = 0x01;        //Timer2 Fosc/4
    T2CON = 0xA0;           //Timer2 ON psc 1:16
    //configuracion de las interrupciones
    INTCON0bits.GIE = 1;
    INTCON0bits.INT0EDG = 0;
    PIE1bits.INT0IE = 1;
    INT0PPS = 0x0C;
    //inicializacion del LCD
    LCD_INIT();
}

void convierte(unsigned int numero){
    diezmillar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola upao");
    while(1){
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("Mensaje en bucle");
    }
}

void __interrupt(irq(INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    switch(estado){
        case 0:
            CCPR1H = 31;
            estado = 1;
            break;
        case 1:
            CCPR1H = 25;
            estado = 2;
            break;
        case 2:
            CCPR1H = 20;
            estado = 3;
            break;
        case 3:
            CCPR1H = 15;
            estado = 4;
            break;
        case 4:
            CCPR1H = 10;
            estado = 5;
            break;
        case 5:
            CCPR1H = 5;
            estado = 6;
            break;
        case 6:
            CCPR1H = 0;
            estado = 0;
            break;
            
    }
}