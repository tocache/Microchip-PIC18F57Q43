/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on June 4, 2026, 8:25 AM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 64000000UL

void configuro(void){
    //conf mod osc
    OSCCON1 = 0x60;
    OSCFRQ = 0x08;
    OSCEN = 0x40;
    //conf las E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    ANSELB = 0xFC;
    WPUB = 0x03;
}

void LCD_init(void){
    LCD_CONFIG();
    __delay_ms(16);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    LCD_init();
    POS_CURSOR(1,0);                        //cursor a la primera linea
    ESCRIBE_MENSAJE("Hola upcino!",12);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Microbios 2026-1",16); //cursor a la segunda linea
    while(1){
    }
    return;
}
