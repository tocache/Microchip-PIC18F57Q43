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
    ADCON0bits.ADFM = 0; //just izq
    RF0PPS = 0x16;
    T2PR = 98;
    CCP2CON = 0x9C;
    CCPR2H = 49;
    CCPR2L = 0;
    T2CLKCON = 0x01;
    T2CON = 0xC0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(17);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("NRC9354 Jue 6PM", 15);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("MICRO CURIOSITY", 15);
    __delay_ms(3000);
    BORRAR_LCD();
}

unsigned char lectura_ADC=0;

void main(void) {
    configuro();
    lcd_init();
    pantallazo();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        lectura_ADC = ADRESH;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("ANA0:",5);
        ENVIA_CHAR((lectura_ADC/100)+0x30);
        ENVIA_CHAR(((lectura_ADC%100)/10)+0x30);
        ENVIA_CHAR((lectura_ADC%10)+0x30);
        CCPR2H = ADRESH;
    }
}
