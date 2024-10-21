/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 14 de octubre de 2024, 10:45 AM
 */

#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#include "MAX7219.h"
#define _XTAL_FREQ 32000000UL

//variables globales
unsigned char variablazo = 0;
unsigned char concatenado[];
unsigned char desplazamiento = 0;
unsigned char deco_centena[];
unsigned char deco_decena[];
unsigned char deco_unidad[];

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
unsigned char vacio[] = {0B00000000,0B00000000,0B00000000,0B00000000,0B00000000,0B00000000,0B00000000,0B00000000};


void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;       //HFINTOSC a 32Mhz
    //conf de las E/S
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
    //conf de Timer0 para timebase de scroll
    T0CON1 = 0x4E;      //FOSC/4 PRES 1:16384
    T0CON0 = 0x80;      //TMR0 enabled, POSTS 1:1
    TMR0H = 146;        //Periodo de temporizado aprox 300ms
    //copnf de las INTs
    PIE3bits.TMR0IE = 1;
    INTCON0bits.GIE = 0;
    PIR3bits.TMR0IF = 0;
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

void decodificacion(unsigned char numero){
    unsigned char centena, decena, unidad;
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
    switch(centena){
        case 0:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_0[i];
            }
            break;
        case 1:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_1[i];
            }
            break;
        case 2:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_2[i];
            }
            break;
        case 3:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_3[i];
            }
            break;
        case 4:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_4[i];
            }
            break;
        case 5:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_5[i];
            }
            break;
        case 6:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_6[i];
            }
            break;
        case 7:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_7[i];
            }
            break;
        case 8:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_8[i];
            }
            break;
        case 9:
            for (int i = 0; i < 8; i++) {
                deco_centena[i] = num_9[i];
            }
            break;
    }
    switch(decena){
        case 0:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_0[i];
            }
            break;
        case 1:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_1[i];
            }
            break;
        case 2:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_2[i];
            }
            break;
        case 3:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_3[i];
            }
            break;
        case 4:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_4[i];
            }
            break;
        case 5:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_5[i];
            }
            break;
        case 6:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_6[i];
            }
            break;
        case 7:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_7[i];
            }
            break;
        case 8:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_8[i];
            }
            break;
        case 9:
            for (int i = 0; i < 8; i++) {
                deco_decena[i] = num_9[i];
            }
            break;
    }
    
    switch(unidad){
        case 0:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_0[i];
            }
            break;
        case 1:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_1[i];
            }
            break;
        case 2:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_2[i];
            }
            break;
        case 3:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_3[i];
            }
            break;
        case 4:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_4[i];
            }
            break;
        case 5:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_5[i];
            }
            break;
        case 6:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_6[i];
            }
            break;
        case 7:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_7[i];
            }
            break;
        case 8:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_8[i];
            }
            break;
        case 9:
            for (int i = 0; i < 8; i++) {
                deco_unidad[i] = num_9[i];
            }
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
    __delay_ms(1500);
    MAX7219_WriteData2(0x01,0xAA);
    MAX7219_WriteData2(0x02,0x55);
    MAX7219_WriteData2(0x03,0xAA);
    MAX7219_WriteData2(0x04,0x55);
    MAX7219_WriteData2(0x05,0xAA);
    MAX7219_WriteData2(0x06,0x55);
    MAX7219_WriteData2(0x07,0xAA);
    MAX7219_WriteData2(0x08,0x55);
    __delay_ms(1500);
    MAX7219_WriteData2(0x01,0x00);
    MAX7219_WriteData2(0x02,0x00);
    MAX7219_WriteData2(0x03,0x00);
    MAX7219_WriteData2(0x04,0x00);
    MAX7219_WriteData2(0x05,0x00);
    MAX7219_WriteData2(0x06,0x00);
    MAX7219_WriteData2(0x07,0x00);
    MAX7219_WriteData2(0x08,0x00);    
    __delay_ms(1500);
    INTCON0bits.GIE = 1;    
    while(1){
        unsigned char cuenta;
        for(cuenta=0;cuenta<200;cuenta++){
            decodificacion(cuenta);
            strcpy(concatenado, vacio);
            strcat(concatenado, deco_centena);
            strcat(concatenado, deco_decena);
            strcat(concatenado, deco_unidad);
            strcat(concatenado, vacio);
            MAX7219_WriteData2(0x01,concatenado[desplazamiento]);
            MAX7219_WriteData2(0x02,concatenado[desplazamiento+1]);
            MAX7219_WriteData2(0x03,concatenado[desplazamiento+2]);
            MAX7219_WriteData2(0x04,concatenado[desplazamiento+3]);
            MAX7219_WriteData2(0x05,concatenado[desplazamiento+4]);
            MAX7219_WriteData2(0x06,concatenado[desplazamiento+5]);
            MAX7219_WriteData2(0x07,concatenado[desplazamiento+6]);
            MAX7219_WriteData2(0x08,concatenado[desplazamiento+7]);
            __delay_ms(100);
        }
    }
}

void __interrupt(irq(IRQ_TMR0)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0;
    LATFbits.LATF3 = !LATFbits.LATF3;
    if(desplazamiento < 40){
        desplazamiento++;
    }
    else{
        desplazamiento = 0;
    }
}

void __interrupt(irq(default)) default_ISR(void){
    
}

