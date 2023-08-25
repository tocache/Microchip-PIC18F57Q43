#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define __XTAL_FREQ 4000000UL

unsigned char diezmillar,millar,centena,decena,unidad;

void configuro(void){
    //configuracion del reloj principal
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISCbits.TRISC2 = 0;
    ANSELCbits.ANSELC2 = 0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    TRISFbits.TRISF1 = 1;
    ANSELFbits.ANSELF1 = 0;
    TRISB = 0xFF;
    ANSELB = 0xEF;
    WPUBbits.WPUB4 = 1;
    //inicializacion del LCD
    LCD_INIT();
    LATCbits.LATC2 = 0;     //contraste al maximo
}

void convierte(unsigned int numero){
    diezmillar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola upao");
    while(1){
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("Mensaje en bucle");
    }
}
