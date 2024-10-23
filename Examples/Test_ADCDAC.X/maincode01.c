/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 23 de octubre de 2024,
 * 
 * 
 *  12:04 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf de la fuente de reloj HFINTOSC a 32MHz
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //conf de las E/S
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    TRISAbits.TRISA2 = 0;
    ANSELAbits.ANSELA2 = 1;
    //conf del ADC
    TRISAbits.TRISA0 = 1;   //RA0 como entrada
    ANSELAbits.ANSELA0 = 1; //RA0 como analogico
    ADCON0bits.FM = 0;      //resultado just izq (8bits en ADRESH)
    ADCON0bits.CS = 1;      //fuente de reloj del ADC en ADCRC
    ADCON0bits.ADON = 1;    //encendemos el ADC    
    //conf del DAC
    DAC1CON = 0xA0;     //DAC enabled, RA2 output, Vref+=Vdd, Vref-=Vss
    DAC1DATL = 0x00;    //DAC salida = 0V
    //conf inicial del LCD
    LCD_INIT();
}

unsigned char tomamuestra_ADC(void){
    ADPCH = 0;              //canal seleccionado RA0
    ADCON0bits.GO = 1;      //toma una muestra
    while(ADCON0bits.GO == 1);  //espero a que termine la toma de muestra
    return ADRESH;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Prueba ADC-DAC");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("con PIC18F57Q43");
    __delay_ms(3000);
    BORRAR_LCD();
    while(1){
        DAC1DATL = tomamuestra_ADC();
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("ADRESH:");
        LCD_ESCRIBE_VAR_CHAR(ADRESH, 3);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("DAC1DATL:");
        LCD_ESCRIBE_VAR_CHAR(DAC1DATL, 3);
    }
}
