/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 20 de octubre de 2025, 05:48 PM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

#define PA_ARRIBA 0
#define PA_ABAJO 1
#define RAPIDO 2
#define LENTO 3

unsigned char sentido = PA_ARRIBA;
unsigned char velocidad = LENTO;
unsigned char cuenta=0;

const unsigned char tbl_nums_7seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                                       0x6D, 0x7D, 0x07, 0x7F, 0x67};

void configuro(void){
    //conf el modulo de oscilador
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;       //RD6 al RD0 son salidas
    ANSELD = 0x80;      //RD6 al RD0 como digitales
    TRISFbits.TRISF1 = 0;   //RF1 como salida
    ANSELFbits.ANSELF1 = 0; //RF1 como digital
    //por defecto los puertos son entradas analógicas
    ANSELBbits.ANSELB2 = 0; //RB2 como digital
    ANSELBbits.ANSELB3 = 0; //RB3 como digital
    WPUBbits.WPUB2 = 1;     //RB2 con pullup
    WPUBbits.WPUB3 = 1;     //RB3 con pullup
    //conf las interrupciones
    INT0PPS = 0x0A;         //INT0 conectado a RB2
    INT1PPS = 0x0B;         //INT1 conectado a RB3
    PIE1bits.INT0IE = 1;    //INT0 enabled
    PIE6bits.INT1IE = 1;    //INT1 enabled
    INTCON0bits.INT0EDG = 0;    //INT0 flanco negativo
    INTCON0bits.INT1EDG = 0;    //INT1 flanco negativo
    INTCON0bits.GIE = 1;    //GIE=1
    //condicionales de operacion
    LATFbits.LATF1 = 0;
}

void main(void) {
    configuro();
    while(1){
        if(sentido == PA_ARRIBA){
            if(cuenta == 9){
                cuenta = 0;
            }
            else{
                cuenta++;
            }
        }
        else if(sentido == PA_ABAJO){
            if(cuenta == 0){
                cuenta = 9;
            }
            else{
                cuenta--;
            }
        }
        LATD = tbl_nums_7seg[cuenta];
        if(velocidad == LENTO){
            __delay_ms(500);
        }
        else if(velocidad == RAPIDO){
            __delay_ms(200);
        }
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;    //bajamos bandera INT0IF
    if(sentido == PA_ARRIBA){
        sentido = PA_ABAJO;
    }
    else if(sentido == PA_ABAJO){
        sentido = PA_ARRIBA;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;    //bajamos bandera INT1IF
    if(velocidad == LENTO){
        velocidad = RAPIDO;
    }
    else if(velocidad == RAPIDO){
        velocidad = LENTO;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}
