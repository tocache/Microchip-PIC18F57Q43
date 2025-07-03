/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 5 de junio de 2025, 02:49 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(18);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);    //y,x
    ESCRIBE_MENSAJE("Microbio UPCino", 15);
    POS_CURSOR(2,0);    //y,x
    ESCRIBE_MENSAJE("Kalun Lau Gan", 13);
    __delay_ms(3000);
    BORRAR_LCD();
    while(1){
        unsigned char x_var;
        POS_CURSOR(1,0);    //y,x
        ESCRIBE_MENSAJE("Loading System", 14);
        POS_CURSOR(2,0);    //y,x
        for(x_var=0;x_var<16;x_var++){
            ENVIA_CHAR('*');
            __delay_ms(500);
        }
        __delay_ms(3000);
        BORRAR_LCD();
        POS_CURSOR(1,3);    //y,x
        ESCRIBE_MENSAJE("FAILED", 6);
        __delay_ms(3000);
    }
}
