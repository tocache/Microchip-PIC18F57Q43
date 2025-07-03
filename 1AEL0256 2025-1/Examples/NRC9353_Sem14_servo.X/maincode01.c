#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //config los pulsadores
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
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
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        if(PORTBbits.RB4 == 0){
            I2C_POS_CURSOR(1,0);
            I2C_ESCRIBE_MENSAJE2("Servo a 000");
            I2C_LCD_CHAR_GRADO();
            LATFbits.LATF5 = 1;
            __delay_us(500);
            LATFbits.LATF5 = 0;
            __delay_us(19500);
        }
        else{
            I2C_POS_CURSOR(1,0);
            I2C_ESCRIBE_MENSAJE2("Servo a 180");
            I2C_LCD_CHAR_GRADO();
            LATFbits.LATF5 = 1;
            __delay_us(2500);
            LATFbits.LATF5 = 0;
            __delay_us(17500);
        }
    }
}
