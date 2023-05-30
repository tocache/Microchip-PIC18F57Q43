/*
 * File:   maincode.c
 * Author: Kalun Lau
 *
 * Created on 29 de mayo de 2023, 10:13 AM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned int cuenta = 0;
unsigned char diezmillar,millar,centena,decena,unidad;

void configuro(void){
    //configuracion del reloj principal
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
    TRISB = 0xFF;
    ANSELB = 0xFC;
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    //inicializacion del LCD
    LCD_INIT();
    LATCbits.LATC1 = 1;     //enciendo el backlight del LCD
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
    ESCRIBE_MENSAJE2("Hola mundo!");
    while(1){
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("Cuenta:");
        convierte(cuenta);
        ENVIA_CHAR(diezmillar+0x30);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        __delay_ms(100);
        cuenta++;
    }
}
