/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 17 de octubre de 2024, 06:54 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(23);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    __delay_ms(50);
}

void main(void){
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Hola mundo UPC!",15);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Microcontrolador",16);
    while(1){
    }
}
