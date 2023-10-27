#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 32000000UL

unsigned int Timer0_16 = 45536;
unsigned int Timer0_OF = 46536;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;        //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S de la aplicacion
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0; //RC0 digital
    //configuración del Timer0
//    T0CON0 = 0x90;      //Timer0 Enabled, 16 bit mode
//    T0CON1 = 0x43;      //Fosc/4, sync, 1:8 pre
//    TMR0H = (Timer0_16 >> 8) & 0x00FF;
//    TMR0L = (Timer0_16 & 0x00FF);
}

void main(void) {
    configuro();
    unsigned int x;
    for(x=0;x<25;x++){
        LATCbits.LATC0 = 1;
        __delay_us(500);
        LATCbits.LATC0 = 0;
        __delay_us(19500);
    }
    for(x=0;x<30;x++){
        LATCbits.LATC0 = 1;
        __delay_us(1500);
        LATCbits.LATC0 = 0;
        __delay_us(18500);
    }
    for(x=0;x<25;x++){
        LATCbits.LATC0 = 1;
        __delay_us(2500);
        LATCbits.LATC0 = 0;
        __delay_us(17500);
    }
    for(x=0;x<30;x++){
        LATCbits.LATC0 = 1;
        __delay_us(1500);
        LATCbits.LATC0 = 0;
        __delay_us(18500);
    }    
}
