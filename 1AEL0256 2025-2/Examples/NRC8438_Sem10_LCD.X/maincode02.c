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

const unsigned char carita_feliz[] = {0x00, 0x1B, 0x1B, 0x00,
                    0x04, 0x11, 0x0E, 0x00};
const unsigned char carita_triste[] = {0x00, 0x1B, 0x1B, 0x00,
                    0x04, 0x00, 0x0E, 0x11};
const unsigned char carita_meh[] = {0x00, 0x1B, 0x09, 0x00,
                    0x04, 0x00, 0x0E, 0x00};

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
    GENERACARACTER(carita_feliz,0);
    GENERACARACTER(carita_triste,1);
    GENERACARACTER(carita_meh,2);
}

void main(void) {
    configuracion();
    LCD_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Hola Mundo UPC!",15);
    POS_CURSOR(2,0);
    /*ESCRIBE_MENSAJE(":)", 2);*/
    ENVIA_CHAR(0);
    ENVIA_CHAR(1);
    ENVIA_CHAR(2);
    while(1){
    }
}
