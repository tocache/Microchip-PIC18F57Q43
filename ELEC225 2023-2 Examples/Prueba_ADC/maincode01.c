//esto es una prueba de proyecto usando el entorno MPLAB Xpress IDE

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;
    OSCEN = 0x40;
    RF3PPS = 0x15;
    //configuracion del PWM
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
    T2PR = 250;
    CCP1CON = 0x9C;
    CCPR1H = 0;
    CCPR1L = 0;
    T2CON = 0xA0;
    T2CLKCON = 0x01;
    LCD_INIT();
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("LED Heart UPC");    
    while(1){
        unsigned char x;
        for(x=0;x<=250;x+=5){
            CCPR1H = 250-x;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("DC:"); 
            LCD_ESCRIBE_VAR_CHAR(CCPR1H, 3);
            __delay_ms(5);
        }
        for(x=0;x<=250;x+=5){
            CCPR1H = x;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("DC:"); 
            LCD_ESCRIBE_VAR_CHAR(CCPR1H, 3);
            __delay_ms(5);
        }        
    }
}