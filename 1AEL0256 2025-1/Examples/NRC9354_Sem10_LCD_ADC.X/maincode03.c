/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 5 de junio de 2025, 06:37 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char cuenta = 0;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //configuracion de las interrupciones
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);        //(pos y, pos x)
    ESCRIBE_MENSAJE("Hola UPCino 2025",16);
    POS_CURSOR(2,0);        //(pos y, pos x)
    ESCRIBE_MENSAJE("Kalun Lau Gan",13);
    __delay_ms(2000);
    BORRAR_LCD();
    while(1){
        for(cuenta=0;cuenta<100;cuenta++){
            POS_CURSOR(1,0);
            ESCRIBE_MENSAJE("Cuenta:", 7);
            ENVIA_CHAR((cuenta / 10) + 0x30);        //decena
            ENVIA_CHAR((cuenta % 10) + 0x30);        //unidad
            __delay_ms(200);
        }
    }
}
