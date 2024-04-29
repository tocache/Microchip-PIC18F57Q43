#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 8000000UL
#define DISPLAY LATD
#define HABILITADOR LATB

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x03;
    OSCEN = 0x40;
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISB = 0xC0;
    ANSELB = 0xC0;
    TRISE = 0xFF;
    ANSELE = 0x00;
    WPUE = 0x03;
}

void nopx4(void){
    __delay_ms(200);
}

void main(void) {
    configuro();
    while(1){
        HABILITADOR = 0x00;
        DISPLAY = 0x73;
        HABILITADOR = 0x01;
        nopx4();
        HABILITADOR = 0x00;
        DISPLAY = 0x38;
        HABILITADOR = 0x02;
        nopx4();
        HABILITADOR = 0x00;
        DISPLAY = 0x3E;
        HABILITADOR = 0x04;
        nopx4();
        HABILITADOR = 0x00;
        DISPLAY = 0x15;
        HABILITADOR = 0x08;
        nopx4();
        HABILITADOR = 0x00;
        DISPLAY = 0x3F;
        HABILITADOR = 0x10;
        nopx4();
        HABILITADOR = 0x00;
        DISPLAY = 0x54;
        HABILITADOR = 0x20;
        nopx4();
    }
}