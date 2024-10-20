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
    //config de las E/S
    TRISBbits.TRISB4 = 1;       //RB4 input
    ANSELBbits.ANSELB4 = 0;     //RB4 digital
    WPUBbits.WPUB4 = 1;         //pullup enabled
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
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE("Estado de RB4",13);
    while(1){
        if(PORTBbits.RB4 == 0){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("PRESIONADO   ", 13);
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("SIN PRESIONAR", 13);
        }
    }
}
