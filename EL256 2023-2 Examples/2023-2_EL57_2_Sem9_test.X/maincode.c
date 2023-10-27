#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;
    OSCEN = 0x40;
}

void lcd_init(void){
    TRISD = 0x00;       //RD salidas
    ANSELD = 0x00;      //RD digitales
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    while(1){
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Hola mundo!", 11);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("Upcino Monterico", 16);
    }
}
