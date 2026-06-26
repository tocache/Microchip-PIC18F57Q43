/*
 * File:   maincode00.c
 * Author: ALUMNOS
 *
 * Created on June 5, 2026, 4:51 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 64000000UL

void configuro(void){
    //conf del mod de osc
    OSCCON1 = 0x60;
    OSCFRQ = 0x08;
    OSCEN = 0x40;
    //conf de las E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    ANSELB = 0xFC;
    WPUB = 0x03;
    //conf del ADC
    ADCON0 = 0x94;      //adc enabled
    ADPCH = 0x00;       //ra0 seleccionado
    ADREF = 0x02;       //activando Vref+ externo
}

void LCD_init(void){
    LCD_CONFIG();
    __delay_ms(21);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Upcino 2026-1",13);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Termometro LM35",15);
    __delay_ms(3000);
    BORRAR_LCD();
}

void main(void) {
    unsigned int resultado_ADC=0;
    configuro();
    LCD_init();
    pantallazo();
    while(1){
        ADCON0bits.GO_nDONE = 1;    //obtenemos una muestra de RA0
        while(ADCON0bits.GO_nDONE == 1); //esperar  q termine de conv
        resultado_ADC = ((ADRESH << 8) + ADRESL) / 41;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Temp LM35:",10);
        ENVIA_CHAR((resultado_ADC/100) + 0x30); //centena de la temp
        ENVIA_CHAR(((resultado_ADC % 100) / 10) + 0x30); //decena de la temp
        ENVIA_CHAR((resultado_ADC % 10) + 0x30); //unidad de la temp
        ENVIA_CHAR(0xDF);
        ENVIA_CHAR('C');
        __delay_ms(500);
    }
    return;
}
