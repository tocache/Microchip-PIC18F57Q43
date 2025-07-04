#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char cuenta = 0;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //configuracion de las INTs
}

void lcd_init(){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(22);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,1);        //(Y,X))
    ESCRIBE_MENSAJE("YA FUNCIONA!!!",14);
    POS_CURSOR(2,2);        //(Y,X))
    ESCRIBE_MENSAJE("UPC Corazon!",12);
    __delay_ms(2000);
    BORRAR_LCD();
    while(1){
        if(cuenta < 151){
            cuenta++;
        }
        else{
            cuenta = 0;
        }
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Contador:", 9);
        ENVIA_CHAR((cuenta / 100) + 0x30);
        ENVIA_CHAR(((cuenta % 100) / 10) + 0x30);
        ENVIA_CHAR((cuenta % 10) + 0x30);
        __delay_ms(100);
    }
}
