/*
 * File:   maincode00.c
 * Author: Alumnos
 *
 * Created on June 3, 2026, 10:28 AM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 64000000UL

void configuro(void){
    //conf mod osc
    OSCCON1 = 0x60;
    OSCFRQ = 0x08;
    OSCEN = 0x40;
    //conf e/s
    TRISD = 0x00;
    ANSELD = 0x00;
    ANSELB = 0xFC;
    WPUB = 0x03;
    //conf adc
    ADCON0 = 0x94;
    ADPCH = 0x00;
    ADREF = 0x02;
}

void LCD_init(void){
    LCD_CONFIG();
    __delay_ms(26);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

unsigned int resultado_ADC = 0;

void main(void) {
    configuro();
    LCD_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Ya funciona!",12);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Micro UPC 2026-1",16);
    __delay_ms(3000);
    BORRAR_LCD();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        resultado_ADC = (ADRESH << 8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("LM35: ",6);
        resultado_ADC = resultado_ADC / 41;
        ENVIA_CHAR(((resultado_ADC % 1000) / 100) + 0x30);
        ENVIA_CHAR(((resultado_ADC % 100) / 10) + 0x30);
        ENVIA_CHAR((resultado_ADC % 10) + 0x30);
        ENVIA_CHAR(0xDF);
        ENVIA_CHAR('C');
    }   
    return;
}
