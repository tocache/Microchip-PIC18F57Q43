/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 12 de junio de 2025, 06:37 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL
#define BACKLAIGHT LATFbits.LATF0
#define ENCENDIDO 1
#define APAGADO 0


void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    ADPCH = 0x00;
    ADCON0bits.ADON = 1;
    ADCON0bits.ADFM = 1; //just der
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(17);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("NRC9354 Jue 6PM", 15);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("MICRO CURIOSITY", 15);
    __delay_ms(3000);
    BORRAR_LCD();
}

unsigned int lectura_ADC=0;

void main(void) {
    configuro();
    lcd_init();
    pantallazo();
    BACKLAIGHT = ENCENDIDO;
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        lectura_ADC = (ADRESH<<8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("ANA0:",5);
        ENVIA_CHAR((lectura_ADC/1000)+0x30);
        ENVIA_CHAR(((lectura_ADC%1000)/100)+0x30);
        ENVIA_CHAR(((lectura_ADC%100)/10)+0x30);
        ENVIA_CHAR((lectura_ADC%10)+0x30);
    }
}
