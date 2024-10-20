/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 18 de octubre de 2024, 09:35 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#include "MAX7219.h"
#define _XTAL_FREQ 32000000UL

void configuro(){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    MAX7219_Init();
    LCD_INIT();
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Prueba MAX7219");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Inicializacion");
    MAX7219_WriteData(0x01, 0x00);      //segment order: DP,A,B,C,D,E,F,G
    MAX7219_WriteData(0x02, 0x5B);
    MAX7219_WriteData(0x03, 0x7E);
    MAX7219_WriteData(0x04, 0x5B);
    MAX7219_WriteData(0x05, 0x3E);
    MAX7219_WriteData(0x06, 0x0E);
    MAX7219_WriteData(0x07, 0x06);
    MAX7219_WriteData(0x08, 0x00);
    __delay_ms(5000);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("CONTADOR:       ");
    MAX7219_WriteData(0x09, 0x0F);
    MAX7219_WriteData(0x08, 0x4E);
    MAX7219_WriteData(0x07, 0x1D);
    MAX7219_WriteData(0x06, 0x15);
    MAX7219_WriteData(0x05, 0x0F);
    while(1){
        unsigned int contador;
        for(contador=0;contador<8000;contador++){
            POS_CURSOR(2,9);
            LCD_ESCRIBE_VAR_INT(contador, 4, 0);
            MAX7219_WriteData(0x04, (contador/1000));
            MAX7219_WriteData(0x03, ((contador%1000)/100));
            MAX7219_WriteData(0x02, ((contador%100)/10));
            MAX7219_WriteData(0x01, (contador%10));
            //__delay_ms(20);
        }

    }
}