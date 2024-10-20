/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 18 de octubre de 2024, 10:27 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char millar, centena, decena, unidad;

void configuro(void){
    //config fuente de reloj
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //config del boton
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 con pullup activo
    //config ADC
    TRISAbits.TRISA0 = 1;   //RA0 como entrada
    ANSELAbits.ANSELA0 = 1; //RA0 como analogico
    ADCON0bits.FM = 1;      //resultado just derecha
    ADCON0bits.CS = 1;      //fuente de reloj del ADC en ADCRC
    ADCON0bits.ADON = 1;    //encendemos el ADC
}

unsigned int tomamuestra_ADC(void){
    ADPCH = 0;              //canal seleccionado RA0
    ADCON0bits.GO = 1;      //toma una muestra
    while(ADCON0bits.GO == 1);  //espero a que termine la toma de muestra
    return ((ADRESH << 8) + ADRESL);
}

conviertemon(unsigned int dato){
    millar = dato / 1000;
    centena = (dato % 1000) / 100;
    decena = (dato % 100) / 10;
    unidad = dato % 10;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(26);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Ejemplo #3",10);
    while(1){
        conviertemon(tomamuestra_ADC());
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("Canal RA0:",10);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
