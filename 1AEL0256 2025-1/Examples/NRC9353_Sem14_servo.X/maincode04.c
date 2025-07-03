#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //config los pulsadores
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //config salida al servo
    TRISFbits.TRISF5 = 0;
    ANSELFbits.ANSELF5 = 0;
    //config de ES para HCSR04
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    TRISCbits.TRISC1 = 1;
    ANSELCbits.ANSELC1 = 0;
    //config de Timer3
    T3CLK = 0x01;
    T3CON = 0x32;
    //config las INTs
    INTCON0bits.GIE = 0;
    //inicializacion de libs
    I2C_LCD_INIT();
    U1_INIT(BAUD_9600);
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Semana 14 UPC");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ultimo minilab");
    U1_STRING_SEND("Semana 14 UPCino Ing Electronica Biomedica Mecatronica");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
    U1_NEWLINE();
}

void main(void) {
    configuro();
    pantallazo();
    while(1){

    }
}

