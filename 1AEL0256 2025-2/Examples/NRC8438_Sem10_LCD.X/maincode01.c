/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 27 de octubre de 2025, 06:01 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuracion(void){
    //conf modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //conf las E/S
    ANSELB = 0xE7;  //RB3 y RB4 digitales
    WPUB = 0x18;    //RB3 y RB4 pullup enabled
}

void LCD_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    __delay_ms(17);
    LCD_CONFIG();
    __delay_ms(18);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuracion();
    LCD_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Hola Mundo UPC!",15);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE(":)", 2);
    while(1){
    }
}
