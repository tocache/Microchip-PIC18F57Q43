#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del oscilador interno para el 57Q43
    OSCCON1 = 0x60;             //HFINTOSC seleccionado
    OSCFRQ = 0x02;              //HFINTOSC a 4MHz
    OSCEN = 0x40;               //HFINTOSC habilitado
    //OSCCON = 0x52;              //INTOSC a 4MHz en 45K50
    //configuracion de E/S
    TRISD = 0x00;               //RD salidas
    ANSELD = 0x00;              //RD digitales
    TRISAbits.TRISA0 = 1;       //RA0 entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 analogica
    TRISEbits.TRISE0 = 0;       //RE0 salida
    ANSELEbits.ANSELE0 = 0;     //RE0 digital
    TRISBbits.TRISB0 = 1;       //RB0 entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 digital
    WPUBbits.WPUB0 = 1;         //RB0 pull-up habilitado
    //INTCON2bits.RBPU = 0;       //pull-up habilitado en RB en 45K50
    TRISCbits.TRISC2 = 0;       //RC2 salida
    ANSELCbits.ANSELC2 = 0;     //RC2 digital
}

void main(void) {
    configuro();
    while(1){
       __delay_ms(200);
       LATEbits.LATE0 = ~LATEbits.LATE0;
    }
}
