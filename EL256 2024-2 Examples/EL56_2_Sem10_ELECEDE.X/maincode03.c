/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 18 de octubre de 2024, 03:52 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char millar, centena, decena, unidad;

void configuro(void){
    //config de la fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config del boton en RB4
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    //config el ADC
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogica
    ADCON0bits.FM = 1;      //res just a la derecha
    ADCON0bits.CS = 1;      //clk source a ADCRC
    ADCON0bits.ADON = 1;    //encendemos el ADC
}

unsigned int tomamuestra_ADC(unsigned char canal){
    ADPCH = canal;              //seleccionamos el canal
    ADCON0bits.GO = 1;          //iniciamos la toma
    while(ADCON0bits.GO == 1);  //esperamos a que termine
    return ((ADRESH << 8) + ADRESL);
}

void convierte(unsigned int dato){
    millar = dato / 1000;
    centena = (dato % 1000) / 100;
    decena = (dato % 100) / 10;
    unidad = dato % 10;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    __delay_ms(50);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Ejercicio No.3",14);
    while(1){
        convierte(tomamuestra_ADC(0));
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("CH0: ",5);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
