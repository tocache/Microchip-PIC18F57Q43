/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 11 de octubre de 2024, 03:42 PM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL
#define LENTASO 0
#define RAPIDASO 1

unsigned char ESTADO = LENTASO;

void configuro(void){
    //config la fuente reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config las E/S
    TRISBbits.TRISB0 = 0;   //RB0 sea salida
    ANSELBbits.ANSELB0 = 0; //RB0 sea digital
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB$ pull-up enabled
    //config de la INT2
    INT2PPS = 0x0C;         //INT2 tenga asignado el RB4
    INTCON0bits.INT2EDG = 0;    //INT2 en flanco negativo
    PIE10bits.INT2IE = 1;   //INT2 habilitada
    INTCON0bits.GIE = 1;    //habilitador global encendido
    PIR10bits.INT2IF = 0;   //bajamos la bandera de INT2
}

void pregunto_delay(void){
    if(ESTADO == RAPIDASO){
        __delay_ms(100);
    }
    if(ESTADO == LENTASO){
        __delay_ms(500);
    }
}

void main(void) {
    configuro();
    while(1){
        LATBbits.LATB0 = 1; //enciendo LED
        pregunto_delay();
        LATBbits.LATB0 = 0; //apagar LED
        pregunto_delay();
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;   //bajamos la bandera de INT2
    if(ESTADO == LENTASO){
        ESTADO = RAPIDASO;
    }
    else if(ESTADO == RAPIDASO){
        ESTADO = LENTASO;
    }
}

void __interrupt(irq(default)) default_ISR(void){
    
}
