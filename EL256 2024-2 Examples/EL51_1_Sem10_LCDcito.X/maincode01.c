/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 16 de octubre de 2024, 01:41 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //config fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;
}

void LCD_INIT(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(16);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    LCD_INIT();
    //me voy a la primera linea del LCD
    POS_CURSOR(1,3);        //(linea,columna)
    ESCRIBE_MENSAJE("Hola mundo", 10);
    //me voy a la primera linea del LCD
    POS_CURSOR(2,2);
    ESCRIBE_MENSAJE("Upcino 2024-2", 13);
    while(1){
    }
}
