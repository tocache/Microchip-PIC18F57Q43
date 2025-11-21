/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 31 de octubre de 2025, 03:45 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

const unsigned char fantasma[] = {0x0E,0x11,0x1B,0x11,
                                    0x11,0x1B,0x15,0x00};

const unsigned char cactus[] = {0x04,0x14,0x15,0x1D,
                                0x07,0x04,0x0E,0x00};

const unsigned char pacman[] = {0x0E,0x11,0x12,0x14,
                                0x12,0x11,0x0E,0x00};

const unsigned char punto[] = {0x00,0x04,0x0E,0x1F,
                                0x0E,0x04,0x00,0x00};

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
}

void rellenar_mapa(void){
    unsigned char x_var;
    POS_CURSOR(1,0);
    for(x_var=0;x_var<16;x_var++){
        ENVIA_CHAR(3);    
    }
    POS_CURSOR(2,0);
    for(x_var=0;x_var<16;x_var++){
        ENVIA_CHAR(3);    
    }
    POS_CURSOR(1, 3);
    ENVIA_CHAR(0);
    POS_CURSOR(1, 6);
    ENVIA_CHAR(0);
    POS_CURSOR(1, 15);
    ENVIA_CHAR(0);
    POS_CURSOR(2, 9);
    ENVIA_CHAR(0);
    POS_CURSOR(2, 12);
    ENVIA_CHAR(0);
    POS_CURSOR(1, 9);
    ENVIA_CHAR(1);
    POS_CURSOR(1, 12);
    ENVIA_CHAR(1);
    POS_CURSOR(2, 3);
    ENVIA_CHAR(1);
    POS_CURSOR(2, 6);
    ENVIA_CHAR(1);
    POS_CURSOR(2, 15);
    ENVIA_CHAR(1);
    POS_CURSOR(1, 0);
    ENVIA_CHAR(2);
}

void LCD_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(23);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(fantasma,0);
    GENERACARACTER(cactus,1);
    GENERACARACTER(pacman,2);
    GENERACARACTER(punto,3);
}

void main(void){
    configuro();
    LCD_init();
    while(1){

    }
}
