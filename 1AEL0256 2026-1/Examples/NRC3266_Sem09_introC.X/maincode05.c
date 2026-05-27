/*
 * File:   maincode00.c
 * Author: Alumnos
 *
 * Created on May 27, 2026, 10:04 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 48000000UL
#define modo1 0
#define modo2 1

const unsigned char tablota[]={0x01, 0x22, 0x40, 0x14,
                                0x08, 0x30, 0x40, 0x06};
unsigned char modo = modo1;

void configuro(void){
    //conf mod de oscilador
    OSCCON1 = 0x60;     //NOSC=HFINTOSC NDIV 1:1
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //conf las E/S
    TRISD = 0x80;       //RD(6:0) salidas
    ANSELD = 0x80;      //RD(6:0) digitales
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0; //RC0 digital
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup enabled
    ANSELBbits.ANSELB1 = 0; //RB1 digital
    WPUBbits.WPUB1 = 1;     //RB1 pullup enabled
    //conf de las interrupts
    PIE6bits.INT1IE = 1;     //INT1 enabled
    INTCON0bits.GIE = 1;     //GIE enabled
    PIR6bits.INT1IF = 0;     //INT1IF abajo
}

void main(void) {
    configuro();
    LATCbits.LATC0 = 1;
    while(1){
        if(modo == modo1){
            for(unsigned char x_var=0;x_var<3;x_var++){
                LATD = tablota[x_var+5];
                if(PORTBbits.RB0 == 0){
                    __delay_ms(100);
                }
                else{
                    __delay_ms(300);
                }
            }
        }
        if(modo == modo2){
            for(unsigned char x_var=0;x_var<5;x_var++){
                LATD = tablota[x_var];
                if(PORTBbits.RB0 == 0){
                    __delay_ms(100);
                }
                else{
                    __delay_ms(300);
                }
            }
            
        }
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    switch(modo){
        case modo1:
            modo = modo2;
            break;
        case modo2:
            modo = modo1;
            break;
    }
}
