#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned int TMR1_ctas = 0;

void configuro(void){
    LCD_INIT();
    //configuracion del Timer1
    T1CLK = 0x01;
    T1CON = 0x02;   //psc 1:1 tmr1 off
    TMR1H = 0x00;
    TMR1L = 0x00;
    TRISCbits.TRISC2 = 1;
    ANSELCbits.ANSELC2 = 0;
}

void splash_screen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Semana 15");
    __delay_ms(3000);
    BORRAR_LCD();
}

void main(void) {
    configuro();
    splash_screen();
    while(1){
        while(PORTCbits.RC2 == 0){
            //rutina del timeout
        }
        T1CONbits.TMR1ON = 1;       //encendemos el Timer1
        while(PORTCbits.RC2 == 1){
            //rutina del timeout
        }
        T1CONbits.TMR1ON = 0;
        TMR1_ctas = (TMR1H << 8) + TMR1L;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("Periodo:");
        LCD_ESCRIBE_VAR_INT((TMR1_ctas*2), 5);
        ESCRIBE_MENSAJE2("us");
        TMR1H = 0;
        TMR1L = 0;
    }
    
}
