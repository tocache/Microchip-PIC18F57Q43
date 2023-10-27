#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion de la fuente de reloj
    OSCCON1 = 0x60;     //HFINTOSC, POSTS 1:1
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;       //HFINTOSC enabled
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(21);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    while(1){
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Hola mundo UPC!",15);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("Kalun Lau Gan",13);
    }
}
