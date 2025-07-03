#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

float temporal;
unsigned int distancia;

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
        LATEbits.LATE0 = 1;
        __delay_us(10);
        LATEbits.LATE0 = 0;
        while(PORTCbits.RC1 == 0);
        TMR3 = 0;
        T3CONbits.TMR3ON = 1;
        while(PORTCbits.RC1 == 1);
        T3CONbits.TMR3ON = 0;
        temporal = TMR3 / 58.31;
        distancia = temporal;
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Dist:");
        I2C_LCD_ESCRIBE_VAR_INT(distancia,3,0);
        I2C_ESCRIBE_MENSAJE2(" cm");
        __delay_ms(500);
    }
}

