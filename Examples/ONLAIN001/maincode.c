#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char estado = 0;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    T0CON0 = 0x80;
    T0CON1 = 0x6B;
    TMR0H = 195;
    RF1PPS = 0x39;
    TRISFbits.TRISF1 = 0;
    ANSELFbits.ANSELF1 = 0;
}

void main(void)    {
    configuro();
    while(1){
        if(PORTBbits.RB4 == 0){
            if(estado == 0){
                estado = 1;
            }
            else{
                estado = 0;
            }
            while(PORTBbits.RB4 == 0){
                __delay_ms(20);
            }
        }
        switch(estado){
            case 0: 
                LATFbits.LATF3 = 0;
                __delay_ms(300);
                LATFbits.LATF3 = 1;
                __delay_ms(300);
                break;
            case 1:
                LATFbits.LATF3 = 0;
                __delay_ms(100);
                LATFbits.LATF3 = 1;
                __delay_ms(100);
                break;
        }
    }
}