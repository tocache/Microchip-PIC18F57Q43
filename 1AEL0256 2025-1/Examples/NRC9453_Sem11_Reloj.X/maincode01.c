/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 12 de junio de 2025, 02:43 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL
#define LUZ_DE_FONDO LATFbits.LATF0

void configuro(void){
    //config del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //config del ADC
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    //vref por defecto Vref+=Vdd, Vref-=Vss
    ADPCH = 0x00;   //leer ANA0
    ADCON0bits.ADFM = 1;    //just derecha
    ADCON0bits.ADON = 1;    //ADC ON
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    LUZ_DE_FONDO = 1;
}

void splash_screen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("LECTURA ADC CH0", 15);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("UPC MICRO 2025-1", 16);
    __delay_ms(3000);
    BORRAR_LCD();
}

unsigned int lectura_ADC = 0;

void main(void) {
    configuro();
    lcd_init();
    splash_screen();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        lectura_ADC = (ADRESH << 8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("ADC CH0:", 8);
        ENVIA_CHAR((lectura_ADC/1000)+0x30);    //millar
        ENVIA_CHAR(((lectura_ADC%1000)/100)+0x30);    //centena
        ENVIA_CHAR(((lectura_ADC%100)/10)+0x30);    //decena
        ENVIA_CHAR((lectura_ADC%10)+0x30);  //unidad
    }
}
