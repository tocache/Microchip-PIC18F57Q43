#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL
#define TON 0
#define TOF 1

unsigned char onda = TON;

unsigned int periodo = 500;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //config el pulsador
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //config salida al servo
    TRISFbits.TRISF5 = 0;
    ANSELFbits.ANSELF5 = 0;
    //
    //config las INTs
    INTCON0bits.GIE = 0;
    //inicializacion de libs
    I2C_LCD_INIT();
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Semana 14 UPC");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ultimo minilab");
    __delay_ms(3000);    
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
    }
}
