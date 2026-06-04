/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on June 4, 2026, 12:41 PM
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
    ADPCH = 0x03;
    ADREF = 0x00;
}

void LCD_init(void){
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void pantallon(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Amigos UPCinos",14);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Microbios 2026-1",16);
    __delay_ms(3000);
    BORRAR_LCD();
}

void main(void) {
    unsigned int resultado = 0;
    configuro();
    LCD_init();
    pantallon();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        resultado = (ADRESH << 8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("ADC RA3:", 8);
        ENVIA_CHAR((resultado /10000) + 0x30);  //imprime diezmillar
        ENVIA_CHAR(((resultado % 10000) / 1000) + 0x30);  //imprime millar
        ENVIA_CHAR(((resultado % 1000) / 100) + 0x30);  //imprime centena
        ENVIA_CHAR(((resultado % 100) / 10) + 0x30);  //imprime decena
        ENVIA_CHAR((resultado % 10) + 0x30);  //imprime unidad
        __delay_ms(100);
    }
    return;
}
