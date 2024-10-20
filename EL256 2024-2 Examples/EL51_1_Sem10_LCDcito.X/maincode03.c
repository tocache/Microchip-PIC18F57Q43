/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 16 de octubre de 2024, 01:41 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int resultado_ADC;
unsigned char millar, centena, decena, unidad;

void configuro(void){
    //config fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //config de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup activado
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogica
    //config del ADC
    ADCON0bits.FM = 1;  //just a la derecha
    ADCON0bits.CS = 1;  //fuente de reloj ADCRC
    ADPCH = 0x00;       //canal RA0/ANA0 seleccionado
    ADREF = 0x00;
    ADCON0bits.ADON = 1;  //encendemos el ADC
}

void LCD_INIT(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(16);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

unsigned int leer_ADC(void){
    ADPCH = 0;
    ADCON0bits.GO = 1;      //inicia la toma de una muestra
    while(ADCON0bits.GO == 1);   //espera a que termine de convertir
    //ya tenemos el resultado de la conversion ADRESH:ADRESL
    return ((ADRESH << 8) + ADRESL);
}

void conversion(unsigned int dato){
    millar = dato / 1000;
    centena = (dato % 1000) / 100;
    decena = (dato % 100) / 10;
    unidad = dato % 10;
}

void main(void) {
    configuro();
    LCD_INIT();
    //me voy a la primera linea del LCD
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Upcino 2024-2", 13);
    while(1){
        resultado_ADC = leer_ADC();
        conversion(resultado_ADC);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("Canal ANA0:", 11);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        __delay_ms(100);
    }
}

