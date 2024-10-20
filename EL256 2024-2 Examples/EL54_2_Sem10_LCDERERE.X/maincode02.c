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
    //conf de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
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
    ESCRIBE_MENSAJE("Ejercicio #2",12);
    while(1){
        if(PORTBbits.RB4 == 0){
            //aqui cuando es verdad
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Boton presionado",16);
        }
        else{
            //aqui cuando es falso
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Boton sin pulsar",16);
        }
    }
}
