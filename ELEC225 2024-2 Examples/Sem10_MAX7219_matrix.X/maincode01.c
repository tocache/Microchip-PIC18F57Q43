/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 14 de octubre de 2024, 10:45 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#include "MAX7219.h"
#define _XTAL_FREQ 32000000UL

//variables globales
unsigned char horas = 11;
unsigned char minutos = 50;
unsigned char segundos = 0;
unsigned char ticks = 0;

unsigned char letra_a[]={0B00110000,0B01111000,0B11001100,0B11001100,0B11111100,0B11001100,0B11001100,0B00000000};
unsigned char num_0[] = {0B01111000,0B11001100,0B11011100,0B11111100,0B11101100,0B11001100,0B01111100,0B00000000}; // 0
unsigned char num_1[] = {0B00110000,0B01110000,0B00110000,0B00110000,0B00110000,0B00110000,0B11111100,0B00000000}; // 1
unsigned char num_2[] = {0B01111000,0B11001100,0B00001100,0B00111000,0B01100000,0B11001100,0B11111100,0B00000000}; // 2
unsigned char num_3[] = {0B01111000,0B11001100,0B00001100,0B00111000,0B00001100,0B11001100,0B01111000,0B00000000}; // 3
unsigned char num_4[] = {0B00011100,0B00111100,0B01101100,0B11001100,0B11111110,0B00001100,0B00011110,0B00000000}; // 4
unsigned char num_5[] = {0B11111100,0B11000000,0B11111000,0B00001100,0B00001100,0B11001100,0B01111000,0B00000000}; // 5
unsigned char num_6[] = {0B00111000,0B01100000,0B11000000,0B11111000,0B11001100,0B11001100,0B01111000,0B00000000}; // 6
unsigned char num_7[] = {0B11111100,0B11001100,0B00001100,0B00011000,0B00110000,0B00110000,0B00110000,0B00000000}; // 7
unsigned char num_8[] = {0B01111000,0B11001100,0B11001100,0B01111000,0B11001100,0B11001100,0B01111000,0B00000000}; // 8
unsigned char num_9[] = {0B01111000,0B11001100,0B11001100,0B01111100,0B00001100,0B00011000,0B01110000,0B00000000}; // 9


void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;       //HFINTOSC a 32Mhz
    //conf del LCD
    LCD_INIT();
    //conf del MAX7219
    MAX7219_Init();
    MAX7219_WriteData2(COM_INTENSITY, 0x0F);
    __delay_ms(100);
}

void MAX7219_WriteAll(unsigned char *dato){
    unsigned char var_x;
    for(var_x=0;var_x<8;var_x++){
        MAX7219_WriteData2(var_x+1, dato[var_x]);
    }
}

void MAX7219_Write_var(unsigned char dato){
    switch(dato){
        case 0:
            MAX7219_WriteAll(num_0);
            break;
        case 1:
            MAX7219_WriteAll(num_1);
            break;
        case 2:
            MAX7219_WriteAll(num_2);
            break;
        case 3:
            MAX7219_WriteAll(num_3);
            break;
        case 4:
            MAX7219_WriteAll(num_4);
            break;
        case 5:
            MAX7219_WriteAll(num_5);
            break;
        case 6:
            MAX7219_WriteAll(num_6);
            break;
        case 7:
            MAX7219_WriteAll(num_7);
            break;
        case 8:
            MAX7219_WriteAll(num_8);
            break;
        case 9:
            MAX7219_WriteAll(num_9);
            break;
    }
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Prueba MAX7219");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Matriz 8x8");
    MAX7219_WriteData2(0x01,0xFF);
    MAX7219_WriteData2(0x02,0x00);
    MAX7219_WriteData2(0x03,0xFF);
    MAX7219_WriteData2(0x04,0x00);
    MAX7219_WriteData2(0x05,0xFF);
    MAX7219_WriteData2(0x06,0x00);
    MAX7219_WriteData2(0x07,0xFF);
    MAX7219_WriteData2(0x08,0x00);
    __delay_ms(3000);
    while(1){
        unsigned char cuenta;
        for(cuenta=0;cuenta<10;cuenta++){
                MAX7219_Write_var(cuenta);
                __delay_ms(200);
        }
    }
}


