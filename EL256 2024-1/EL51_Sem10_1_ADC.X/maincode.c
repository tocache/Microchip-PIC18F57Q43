/*
 * File:   maincode.c
 * Author: klnla
 *
 * Created on 22 de mayo de 2024, 01:35 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion del ADC
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogica
    ADCON0 = 0x94;      //ADC on, just. derecha, ADCRC, no continuo
}

void leer_ADC(void){
    ADPCH = 0x00;       //ANA0 seleccionado
    ADCON0bits.GO = 1;  //iniciamos la toma de una muestra
    while(ADCON0bits.GO == 1);
    //el resultado esta en ADRESH:ADRESL
}

void main(void) {
    unsigned int valor_leido = 0;
    float voltaje = 0;
    unsigned int final = 0;
    configuro();
    LCD_INIT();
    __delay_ms(500);
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE("Ejemplo Sem.10",14);
    POS_CURSOR(2,1);
    ENVIA_CHAR(0xE4);
    ESCRIBE_MENSAJE("C PIC18F57Q43",13);
    __delay_ms(3000);
    BORRAR_LCD();
    while(1){
        leer_ADC();
        valor_leido = (ADRESH<<8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Lectura AN-0:",13);
        POS_CURSOR(2,0);
        ENVIA_CHAR((valor_leido / 10000) + 0x30);   //mostrando dig diez_millar
        ENVIA_CHAR(((valor_leido % 10000) / 1000) + 0x30); //muestra dig millar
        ENVIA_CHAR(((valor_leido % 1000) / 100) + 0x30); //muestra dig centena
        ENVIA_CHAR(((valor_leido % 100) / 10) + 0x30);  //muestra dig decena
        ENVIA_CHAR((valor_leido % 10) + 0x30);  //muestra dig unidad
        voltaje = valor_leido * 0.122;          //escalamiento a voltaje
        final = voltaje;                    //conversion float-integer
        POS_CURSOR(2,8);
        ENVIA_CHAR(((final % 1000) / 100) + 0x30); //muestra dig centena
        ENVIA_CHAR('.');
        ENVIA_CHAR(((final % 100) / 10) + 0x30);  //muestra dig decena
        ENVIA_CHAR((final % 10) + 0x30);  //muestra dig unidad
        ENVIA_CHAR('V');
    }
}
