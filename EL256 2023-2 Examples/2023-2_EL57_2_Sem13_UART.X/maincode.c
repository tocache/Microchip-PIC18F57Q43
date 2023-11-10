#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;         //HFINTOSC div 1:1
    OSCFRQ = 0x06;          //HFINTOSC a 32MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;   //RA0 como entrada
    ANSELAbits.ANSELA0 = 1; //RA0 como analogico
    TRISBbits.TRISB0 = 1;   //RB0 como entrada
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup activada
    TRISBbits.TRISB1 = 1;   //RB1 como entrada
    ANSELBbits.ANSELB1 = 0; //RB1 como digital
    WPUBbits.WPUB1 = 1;     //RB1 pullup activada
    TRISCbits.TRISC0 = 0;   //RC0 como salida
    ANSELCbits.ANSELC0 = 0; //RC0 como digital
    TRISCbits.TRISC1 = 0;   //RC1 como salida
    ANSELCbits.ANSELC1 = 0; //RC1 como digital
    TRISFbits.TRISF0 = 0;   //RF0 como salida
    ANSELFbits.ANSELF0 = 0; //RF0 como digital
    TRISFbits.TRISF1 = 1;   //RF1 como entrada
    ANSELFbits.ANSELF1 = 0; //RF1 como digital
    //inicialixscion del LCD
    LCD_INIT();
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola Semana 13");
    while(1){
        unsigned char x;
        for(x=0;x<100;x++){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("Cuenta:");
            LCD_ESCRIBE_VAR_CHAR(x, 3);
            __delay_ms(30);
        }
        for(x=100;x>0;--x){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("Cuenta:");
            LCD_ESCRIBE_VAR_CHAR(x, 3);
            __delay_ms(30);
        }
    }
}
