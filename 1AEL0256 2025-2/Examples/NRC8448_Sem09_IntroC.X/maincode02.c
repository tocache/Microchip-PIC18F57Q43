/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 24 de octubre de 2025, 10:19 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

const unsigned char efectazo[] = {0x01, 0x02, 0x40, 0x10,
                                0x08, 0x04, 0x40, 0x20};
const unsigned char deco7s[] = {0x3F, 0x06, 0x5B, 0x4F,
                                0x66, 0x6D, 0x7D, 0x07,
                                0x7F, 0x67, 0x5F, 0x7C,
                                0x58, 0x5E, 0x7B, 0x71};
unsigned char cuenta_actual = 0;

void configuro(void){
    //conf el modulo de oscilador}
    OSCCON1 = 0x60; //NOSC HFINTOSC NDIV 1:1
    OSCFRQ = 0x02;  //HFINTOSC 4MHz
    OSCEN = 0x40;   //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;   //RD(6:0) salidas
    ANSELD = 0x80;  //RD(6:0) digitales
    TRISEbits.TRISE0 = 0;   //RE0 salida
    ANSELEbits.ANSELE0 = 0; //RE0 digital
    TRISFbits.TRISF0 = 0;   //RF0 salida
    ANSELFbits.ANSELF0 = 0; //RF0 digital
    ANSELB = 0xC7;  //RB3, RB4, RB5 digitales
    WPUBbits.WPUB5 = 1; //RB5 pullup enabled
    //conf interrupciones
    INT0PPS = 0x0B; //INT0 viene de RB3
    INT1PPS = 0x0C; //INT1 viene de RB4
    INT2PPS = 0x0D; //INT2 viene de RB5
    PIE1bits.INT0IE = 1;    //INT0 enabled
    PIE6bits.INT1IE = 1;    //INT1 enabled
    PIE10bits.INT2IE = 1;   //INT2 enabled
    INTCON0bits.GIE = 1;     //global interrupt enabled
    INTCON0bits.INT1EDG = 0;    //INT1 falling edge
    INTCON0bits.INT2EDG = 0;    //NT2 falling edge
}

void pantallazo(void){
    unsigned char x_var,y_var;
    for(y_var=0;y_var<10;y_var++){
        for(x_var=0;x_var<8;x_var++){
            LATD = efectazo[x_var];
            __delay_ms(50);
        }
    }
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        //prueba 1: prender un apagar los LEDs
        /*LATEbits.LATE0 = 1;
        LATFbits.LATF0 = 0;
        __delay_ms(500);
        LATFbits.LATF0 = 1;
        LATEbits.LATE0 = 0;
        __delay_ms(500);*/
        //prueba 2: probar los sensores
        /*if(PORTBbits.RB3 == 1){     //sensor Hall
            LATEbits.LATE0 = 1;
        }
        else{
            LATEbits.LATE0 = 0;
        }
        if(PORTBbits.RB4 == 0){     //sensor LDR
            LATFbits.LATF0 = 1;
        }
        else{
            LATFbits.LATF0 = 0;
        }*/
        LATD = deco7s[cuenta_actual];
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;    //bajamos flag INT0IF
    if(cuenta_actual == 15){
        cuenta_actual = 0;
    }
    else{
        cuenta_actual++;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;    //bajamos flag INT0IF
    if(cuenta_actual == 0){
        cuenta_actual = 15;
    }
    else{
        cuenta_actual--;
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;    //bajamos flag INT0IF
    cuenta_actual = 0;
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
}
