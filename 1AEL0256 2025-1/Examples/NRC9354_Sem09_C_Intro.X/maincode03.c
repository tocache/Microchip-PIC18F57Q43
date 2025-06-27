/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 29 de mayo de 2025, 07:02 PM
 */
//This is a comment, you must use // before each comment or /**/ for multi-line
//comments

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISD = 0x80;
    ANSELD = 0x80;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB0 = 0;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    //configuracion de las interrupciones INT0 e INT1
    INT0PPS = 0x08;     //asignar INT0 en RB0
    INT1PPS = 0x09;     //asignar INT1 en RB1
    PIE1bits.INT0IE = 1;    //INT0 activada
    PIE6bits.INT1IE = 1;    //INT1  activada
    INTCON0bits.INT0EDG = 0;    //INT0 deteccion flanco negativo
    INTCON0bits.INT1EDG = 0;    //INT1 deteccion flanco descendente
    INTCON0bits.GIE = 1;        //habilitador global activado
}

unsigned char mensaje1[]={0x71, 0x77, 0x30, 0x38, 0x00};  //FAIL
unsigned char mensaje2[]={0x7C, 0x10, 0x58, 0x5F, 0x00};  //bica
unsigned char visual = 0;   //'0' para mensaje1 y '1' para mensaje2
unsigned char velocidad = 0;    //'0' para lento, '1' para rapido


void main(void) {
    configuro();
    while(1){
        if(visual == 0){
            unsigned char x_var;
            for(x_var=0;x_var<5;x_var++){
                LATD = mensaje1[x_var];
                if(velocidad == 0){
                    __delay_ms(500);
                }
                else{
                    __delay_ms(200);
                }
            }
        }
        else{
            unsigned char x_var;
            for(x_var=0;x_var<5;x_var++){
                LATD = mensaje2[x_var];
                if(velocidad == 0){
                    __delay_ms(500);
                }
                else{
                    __delay_ms(200);
                }
            }
        }
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;    //se baja la bandera INT0IF
    if(visual == 0){
        visual = 1;
    }
    else{
        visual = 0;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;    //se baja la bandera INT0IF
    if(velocidad == 0){
        velocidad = 1;
    }
    else{
        velocidad = 0;
    }
}


