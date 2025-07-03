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
unsigned char persona0[] = {0x10,0x10,0x00,0x10,
                            0x00,0x00,0x00,0x10};
unsigned char persona1[] = {0x18,0x18,0x10,0x14,
                            0x18,0x10,0x08,0x04};
unsigned char persona2[] = {0x0C,0x0C,0x08,0x0A,
                            0x0C,0x08,0x14,0x12};
unsigned char persona3[] = {0x06,0x06,0x14,0x0E,
                            0x05,0x04,0x0A,0x19};
unsigned char persona4[] = {0x03,0x03,0x02,0x07,
                            0x0A,0x02,0x05,0x0C};
unsigned char persona5[] = {0x01,0x01,0x01,0x03,
                            0x05,0x01,0x03,0x06};
unsigned char persona6[] = {0x00,0x00,0x00,0x01,
                            0x02,0x00,0x01,0x03};
unsigned char persona7[] = {0x00,0x00,0x00,0x00,
                            0x01,0x00,0x00,0x01};



void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(18);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(persona0, 0);
    GENERACARACTER(persona1, 1);
    GENERACARACTER(persona2, 2);
    GENERACARACTER(persona3, 3);
    GENERACARACTER(persona4, 4);
    GENERACARACTER(persona5, 5);
    GENERACARACTER(persona6, 6);
    GENERACARACTER(persona7, 7);
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
            __delay_ms(100);
        }
        __delay_ms(3000);
        BORRAR_LCD();
        POS_CURSOR(1,3);    //y,x
        ESCRIBE_MENSAJE("FAILED", 6);
        unsigned char y_var;
        for(y_var=0;y_var<16;y_var++){
            for(x_var=0;x_var<8;x_var++){
                POS_CURSOR(2,y_var);    //y,x
                ENVIA_CHAR(x_var);
                __delay_ms(200);
            }
        }
        BORRAR_LCD();
    }
}
