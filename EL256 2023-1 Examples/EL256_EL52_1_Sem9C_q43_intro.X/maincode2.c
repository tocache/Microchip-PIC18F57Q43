#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char e_acento[]={0x02,0x04,0x0E,0x11,0x1F,0x10,0x0E,0x00};

void configuro(void){
    //configuracion del oscilador interno para el 57Q43
    OSCCON1 = 0x60;             //HFINTOSC seleccionado
    OSCFRQ = 0x02;              //HFINTOSC a 4MHz
    OSCEN = 0x40;               //HFINTOSC habilitado
    //OSCCON = 0x52;              //INTOSC a 4MHz en 45K50
    //configuracion de E/S
    TRISD = 0x00;               //RD salidas
    ANSELD = 0x00;              //RD digitales
    TRISAbits.TRISA0 = 1;       //RA0 entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 analogica
    TRISEbits.TRISE0 = 0;       //RE0 salida
    ANSELEbits.ANSELE0 = 0;     //RE0 digital
    TRISBbits.TRISB0 = 1;       //RB0 entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 digital
    WPUBbits.WPUB0 = 1;         //RB0 pull-up habilitado
    //INTCON2bits.RBPU = 0;       //pull-up habilitado en RB en 45K50
    TRISCbits.TRISC2 = 0;       //RC2 salida
    ANSELCbits.ANSELC2 = 0;     //RC2 digital
    LATCbits.LATC2 = 1;         //Encendemos el backlight del LCD
}

void LCD_Init(void){
    __delay_ms(29);
    LCD_CONFIG();
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(e_acento,0);
}

void main(void) {
    configuro();
    LCD_Init();
    while(1){
        POS_CURSOR(1,2);
        ESCRIBE_MENSAJE2("Hola mundo!");
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("Con fe aprobar",14);
        ENVIA_CHAR(0);
        ENVIA_CHAR('!');
    }
}
