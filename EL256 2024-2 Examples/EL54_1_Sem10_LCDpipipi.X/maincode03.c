/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 17 de octubre de 2024, 02:40 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char millar,centena,decena,unidad;

void configuro(void){
    //config fuente de reloj
    OSCCON1 = 0x60; //NOSC=HFINTOSC NDIV=1:1
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;   //HFINTOSC enabled
    //config del RB4
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 con pullup
    //config el ADC
    TRISAbits.TRISA0 = 1;   //RA0 es entrada
    ANSELAbits.ANSELA0 = 1; //RA0 es analogica
    ADCON0bits.FM = 1;      //resultado just derecha
    ADCON0bits.CS = 1;      //fuente de reloj del ADC en ADCRC
    ADCON0bits.ADON = 1;    //enciendo el ADC
}

unsigned int tomamuestra_ADC(void){
    ADPCH = 0;      //selecciono el canal RA0/ANA0
    ADCON0bits.GO = 1;  //procede a tomar una muestra
    while(ADCON0bits.GO == 1);  //espera a que termine
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
    __delay_ms(21);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Tercer ejemplo:",15);
    while(1){
        convierte(tomamuestra_ADC());
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("CH0:",4);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
