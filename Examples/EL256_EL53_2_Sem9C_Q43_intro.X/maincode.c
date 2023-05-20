#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL    //frecuencia de trabajo

void configuro(void){
    //configuracion del oscilador interno
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISD = 0x00;           //RD como salidas
    ANSELD = 0x00;          //RD como digitales
    TRISAbits.TRISA0 = 1;   //RA0 como entrada
    ANSELAbits.ANSELA0 = 1; //RA0 como analogica
    TRISBbits.TRISB0 = 1;   //RB0 como entrada
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup activadas
    TRISEbits.TRISE0 = 0;   //RE0 como salida
    ANSELEbits.ANSELE0 = 0; //RE0 como digital
}

void main(void) {
    configuro();
    while(1){
        __delay_ms(100);
        LATEbits.LATE0 = ~LATEbits.LATE0;
    }
}
