/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on June 5, 2026, 10:32 AM
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
    //conf E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    ANSELB = 0xFC;
    WPUB = 0x03;
    //conf ADC
    ADCON0 = 0x94;
    ADPCH = 0x00;       //seleccionar RA0/ANA0
    ADREF = 0x02;
}

void LCD_init(void){
    LCD_CONFIG();
    __delay_ms(18);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

unsigned int resultado_ADC = 0;

void main(void) {
    configuro();
    LCD_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Hola upcino!",12);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Micros 2026-1",13);
    __delay_ms(3000);
    BORRAR_LCD();
    while(1){
        ADCON0bits.GO_nDONE = 1;    //ADC toma una muestra
        while(ADCON0bits.GO_nDONE == 1); //esperar a que termine
        resultado_ADC = ((ADRESH << 8) + ADRESL) / 41;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Temp LM35:", 10);
        ENVIA_CHAR((resultado_ADC / 100) + 0x30);   //centena de la temp
        ENVIA_CHAR(((resultado_ADC % 100) / 10) + 0x30); //decena de la temp
        ENVIA_CHAR((resultado_ADC % 10) + 0x30); //unidad de la temp
        ENVIA_CHAR(0xDF);
        ENVIA_CHAR('C');
        __delay_ms(500);
    }
    return;
}
