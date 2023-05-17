#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion de fuente de reloj al CPU:
    OSCCON1 = 0x60;         //HFINTOSC
    OSCFRQ = 0x02;          //HFINTOSC a 4MHz
    OSCEN = 0x40;           //HFINTOSC habilitado
    //configuracion de E/S:
    TRISD = 0x00;           //RD salidas
    ANSELD = 0x00;          //RD digitales
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogica
    TRISBbits.TRISB0 = 1;   //RB0 entrada
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup activado
    TRISCbits.TRISC2 = 0;   //RC2 salida
    ANSELCbits.ANSELC2 = 0; //RC2 digital
}

void main(void) {
    configuro();
    while(1){
        LATCbits.LATC2 = 1;
        __delay_ms(200);
        LATCbits.LATC2 = 0;
        __delay_ms(200);
    }
}
