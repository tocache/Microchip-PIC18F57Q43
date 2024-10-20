/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 16 de octubre de 2024, 05:30 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char millar, centena, decena, unidad;

void configuro(void){
    //config de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //config de las E/S
    TRISBbits.TRISB4 = 1;       //RB4 input
    ANSELBbits.ANSELB4 = 0;     //RB4 digital
    WPUBbits.WPUB4 = 1;         //pullup enabled
    //config del ADC
    TRISAbits.TRISA0 = 1;       //RA0 input
    ANSELAbits.ANSELA0 = 1;     //RA0 analog
    ADCON0bits.FM = 1;          //just a la derecha
    ADCON0bits.CS = 1;          //fuente de reloj ADCRC
    ADCON0bits.ADON = 1;        //ADC encendido
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(17);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

unsigned int toma_muestra(void){
    ADPCH = 0x00;
    ADCON0bits.GO = 1;      //toma una muestra
    while(ADCON0bits.GO == 1);  //va a esperar a que termine de convertir
    return ((ADRESH << 8) + ADRESL);
}

void convierte(unsigned int dato){
    millar = dato / 1000;
    centena = (dato % 1000) / 100;
    decena = (dato % 100) / 10;
    unidad = dato % 10;
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Lectura ADC",11);
    while(1){
        convierte(toma_muestra());
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("CH0: ",5);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        __delay_ms(50);
    }
}
