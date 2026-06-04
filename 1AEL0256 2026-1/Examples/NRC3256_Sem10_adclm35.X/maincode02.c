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
    ADREF = 0x02;       //conf del vref del ADC a Vref+ externo
    ADPCH = 0x00;       //seleccionar la fuente analogica (RA0)
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
        resultado_ADC = resultado_ADC / 41;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("LM35: ",6);
        ENVIA_CHAR((resultado_ADC / 1000) + 0x30);      //centena
        ENVIA_CHAR(((resultado_ADC % 100) / 10) + 0x30);//decena
        ENVIA_CHAR((resultado_ADC % 10) + 0x30);        //unidad
        ENVIA_CHAR(0xDF);
        ENVIA_CHAR('C');
        __delay_ms(500);
    }
    return;
}
