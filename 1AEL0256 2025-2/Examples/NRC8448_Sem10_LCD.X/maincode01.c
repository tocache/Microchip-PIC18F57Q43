/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 31 de octubre de 2025, 10:12 AM
 */
#include <xc.h>}
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x06;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
}

void LCD_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(21);
    BORRRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    LCD_init();
    while(1){
        
    }
}
