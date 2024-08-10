/*
 * File:   maincode.c
 * Author: klnla
 *
 * Created on 22 de mayo de 2024, 05:30 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int resultado = 0;
float escalamiento = 0;
unsigned int intermedio = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion del A/D
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogica
    ADCON0 = 0x94;  //ADC conv manual, ADCRC, just der, ADC on
}

void LCD_inicia(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    __delay_ms(21);
    LCD_CONFIG();
    __delay_ms(22);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    __delay_ms(100);
}

unsigned int leer_ADC(unsigned char canal){
    ADPCH = canal;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return((ADRESH<<8)+ADRESL);
}

void main(void) {
    configuro();
    LCD_inicia();
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE("Bienvenido UPC",14);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("INGENIERIA  2024",16);
    __delay_ms(5000);
    BORRAR_LCD();
    while(1){
        resultado = leer_ADC(0);
        POS_CURSOR(1,1);
        ESCRIBE_MENSAJE("Lectura de RA0", 14);
        POS_CURSOR(2,0);
        ENVIA_CHAR((resultado / 10000) + 0x30); //digito diez millar
        ENVIA_CHAR(((resultado % 10000) / 1000) + 0x30); //digito millar
        ENVIA_CHAR(((resultado % 1000) / 100) + 0x30); //digito centena
        ENVIA_CHAR(((resultado % 100) / 10) + 0x30); //digito decena
        ENVIA_CHAR((resultado % 10) + 0x30); //digito unidad
        __delay_ms(100);
        escalamiento = resultado / 0.122;
        intermedio = escalamiento;      //pasar float a unsigned int
        POS_CURSOR(2,8);
        ENVIA_CHAR(((intermedio % 1000) / 100) + 0x30); //muestra dig centena
        ENVIA_CHAR('.');
        ENVIA_CHAR(((intermedio % 100) / 10) + 0x30);  //muestra dig decena
        ENVIA_CHAR((intermedio % 10) + 0x30);  //muestra dig unidad
        ENVIA_CHAR('V');        
    }
}
