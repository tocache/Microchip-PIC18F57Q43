/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on June 4, 2026, 8:25 AM
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
    //conf las E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    ANSELB = 0xFC;
    WPUB = 0x03;
    //conf ADC
    ADCON0 = 0x94;      //conf del ADC
    ADREF = 0x00;       //conf del vref del ADC
    ADPCH = 0x03;       //seleccionar la fuente analogica (RA3)
}

void LCD_init(void){
    LCD_CONFIG();
    __delay_ms(16);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

unsigned int resultado_ADC = 0;

void main(void) {
    configuro();
    LCD_init();
    POS_CURSOR(1,0);                        //cursor a la primera linea
    ESCRIBE_MENSAJE("Hola upcino!",12);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Microbios 2026-1",16); //cursor a la segunda linea
    __delay_ms(3000);
    BORRAR_LCD();
    while(1){
        ADCON0bits.GO_nDONE = 1;        //tomamos una muestra en RA3
        while(ADCON0bits.GO_nDONE == 1);    //esperamos a q termine de convfertir
        resultado_ADC = (ADRESH << 8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Pot RA3:",8);
        ENVIA_CHAR((resultado_ADC / 10000) + 0x30);
        ENVIA_CHAR(((resultado_ADC % 10000) / 1000) + 0x30);
        ENVIA_CHAR(((resultado_ADC % 1000) / 100) + 0x30);
        ENVIA_CHAR(((resultado_ADC % 100) / 10) + 0x30);
        ENVIA_CHAR((resultado_ADC % 10) + 0x30);
    }
    return;
}
