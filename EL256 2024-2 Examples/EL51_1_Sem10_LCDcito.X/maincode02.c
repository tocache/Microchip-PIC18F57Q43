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
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup activado
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
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Upcino 2024-2", 13);
    while(1){
        if(PORTBbits.RB4 == 0){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Pulsador: ON ",13);
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Pulsador: OFF",13);
        }
    }
}

