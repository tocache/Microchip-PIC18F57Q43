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
    //WS2812_INIT();
    //conf de E/S
    TRISCbits.TRISC0 = 1;
    ANSELCbits.ANSELC0 = 0;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
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
    WS2812_DATA_SEND(0,0,0);
    I2C_BORRAR_LCD();
}

unsigned int read_HCSR04(void){
    unsigned int tiempo=0;
    float intermedio=0;
    unsigned int distancia_cm=0;
    LATCbits.LATC1 = 1;
    __delay_us(10);
    LATCbits.LATC1 = 0;
    while(PORTCbits.RC0 == 0);
    while(PORTCbits.RC0 == 1){
        tiempo++;
        __delay_us(1);
    }
    intermedio = tiempo / 58.31;
    distancia_cm = intermedio;
    return distancia_cm;
}

void main(void) {
    configuro();
    splash_screen();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2(" Distanciometro");
    while(1){
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("HCSR04: ");
        I2C_LCD_ESCRIBE_VAR_INT(read_HCSR04(),3, 0);
        I2C_ESCRIBE_MENSAJE2(" cm  ");
        __delay_ms(500);
    }
}
