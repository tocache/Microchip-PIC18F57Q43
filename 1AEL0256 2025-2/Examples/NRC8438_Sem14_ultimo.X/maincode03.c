
#include <pic18f57q43.h>

/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 24 de noviembre de 2025, 05:55 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inicializacion de librerias
    I2C_LCD_INIT();
    //conf de E/S
    TRISCbits.TRISC0 = 1;
    ANSELCbits.ANSELC0 = 0;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
    //conf del Timer1
    T1CLK = 0x01;
    T1CON = 0x32;
    TMR1H = 0;
    TMR1L = 0;
}

void splash_screen(void){
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

}

unsigned int read_HCSR04(void){
    TMR1H = 0;
    TMR1L = 0;
    float intermedio=0;
    unsigned int distancia_cm=0;
    LATCbits.LATC1 = 1;
    __delay_us(10);
    LATCbits.LATC1 = 0;
    while(PORTCbits.RC0 == 0);
    T1CONbits.TMR1ON = 1;
    while(PORTCbits.RC0 == 1);
    T1CONbits.TMR1ON = 0;
    intermedio = ((TMR1H<<8) + TMR1L) / 58.31;
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

