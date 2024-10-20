/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 16 de octubre de 2024, 05:30 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //config de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(17);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Hola upcino",11);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Biomecaele 20242",16);
    while(1){
    }
}
