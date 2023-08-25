#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL        //Frecuencia de trabajo

#define FOQUITO LATFbits.LATF3
#define APAGAO 1
#define PRENDIDO 0
#define BOTON PORTBbits.RB4
#define PRESIONAO 0
#define SOLTAO 1

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HTINTOSC habilitado
    TRISBbits.TRISB4 = 1;           //RB4 entrada
    ANSELBbits.ANSELB4 = 0;         //RB4 digital
    WPUBbits.WPUB4 = 1;             //Weak pullup en RB4 habilitada
    TRISFbits.TRISF3 = 0;           //RF3 salida
    ANSELFbits.ANSELF3 = 0;         //RF3 digital
}

void main(void) {
    configuro();
    while(1){
        if(BOTON == PRESIONAO){
            FOQUITO = PRENDIDO;
            __delay_ms(500);
            FOQUITO = APAGAO;
            __delay_ms(500);
        }
        else{
            FOQUITO = APAGAO;
        }
    }
}
