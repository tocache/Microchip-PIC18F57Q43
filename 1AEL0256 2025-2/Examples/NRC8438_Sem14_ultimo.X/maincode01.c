/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 24 de noviembre de 2025, 05:55 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_WS2812.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inicializacion de librerias
    I2C_LCD_INIT();
    WS2812_INIT();
}

void splash_screen(void){
    WS2812_DATA_SEND(0,0,0);
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Micro Sem14 ULTI");
    I2C_POS_CURSOR(2,0);
    __delay_ms(1000);
    I2C_ESCRIBE_MENSAJE2("Loading");
    for(unsigned char y_var=7;y_var<14;y_var++){
        I2C_POS_CURSOR(2,y_var);
        I2C_ENVIA_LCD_DATA(0xA5);
        __delay_ms(100);
        I2C_POS_CURSOR(2,y_var);
        I2C_ESCRIBE_MENSAJE2("-");
        __delay_ms(100);
        I2C_POS_CURSOR(2,y_var);
        I2C_ESCRIBE_MENSAJE2("+");
        __delay_ms(100);
        I2C_POS_CURSOR(2,y_var);
        I2C_ESCRIBE_MENSAJE2("*");
        __delay_ms(100);
        I2C_POS_CURSOR(2,y_var);
        I2C_ESCRIBE_MENSAJE2(".");
        __delay_ms(100);
    }
    I2C_ESCRIBE_MENSAJE2("OK");
    __delay_ms(4000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    splash_screen();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("WS2812 Neopixel");
    while(1){
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Color: Rojo    ");
        WS2812_DATA_SEND(0,255,0);
        __delay_ms(500);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Color: Verde   ");
        WS2812_DATA_SEND(255,0,0);
        __delay_ms(500);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Color: Azul    ");
        WS2812_DATA_SEND(0,0,255);
        __delay_ms(500);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Color: Amarillo");
        WS2812_DATA_SEND(255,255,0);
        __delay_ms(500);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Color: Naranja ");
        WS2812_DATA_SEND(100,255,0);
        __delay_ms(500);        
    }
}
