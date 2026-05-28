/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on May 28, 2026, 11:54 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 48000000UL
#define s_izq 0
#define s_der 1

void configuro(void){
    //conf el mod de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;
    OSCEN = 0x40;
    //conf las E/S
    TRISD = 0x80;
    ANSELD = 0x80;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    ANSELB = 0xFC;
    WPUB = 0x03;
    //conf de las ints
    PIE1bits.INT0IE = 1;    //activar INT0
    PIR1bits.INT0IF = 0;    //bvajamos bandera INT0IF
    INTCON0bits.GIE = 1;
}

unsigned char animacion[]={0x11,0x22,0x05,0x0A,0x14,0x28};
__bit sentido = s_izq;

void main(void) {
    configuro();
    LATCbits.LATC0 = 1;
    while(1){
        for(unsigned char x_var=0;x_var<6;x_var++){
            if(sentido == s_izq){
                LATD = animacion[5-x_var];
            }
            if(sentido == s_der){
                LATD = animacion[x_var];
            }
            __delay_ms(200);
        }
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;        //bajamos bandera INT0
    if(sentido == s_izq){
        sentido = s_der;
    }
    else{
        sentido = s_izq;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}