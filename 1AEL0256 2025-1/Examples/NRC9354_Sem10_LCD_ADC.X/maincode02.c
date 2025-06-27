/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 5 de junio de 2025, 06:37 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char estado = 0;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //configuracion de las interrupciones
    INT2PPS = 0x0C;
    PIE10bits.INT2IE = 1;
    PIR10bits.INT2IF = 0;
    INTCON0bits.INT2EDG = 0;
    INTCON0bits.GIE = 1;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);        //(pos y, pos x)
    ESCRIBE_MENSAJE("Hola UPCino 2025",16);
    POS_CURSOR(2,0);        //(pos y, pos x)
    ESCRIBE_MENSAJE("Kalun Lau Gan",13);
    __delay_ms(2000);
    BORRAR_LCD();
    while(1){
        INTCON0bits.GIE = 0;
        switch(estado){
            case 0:
                POS_CURSOR(1,3);        //(pos y, pos x)
                ESCRIBE_MENSAJE("Ingenieria",10);
                POS_CURSOR(2,2);        //(pos y, pos x)
                ESCRIBE_MENSAJE("Electronica",11);
                break;
            case 1:
                POS_CURSOR(1,3);        //(pos y, pos x)
                ESCRIBE_MENSAJE("Ingenieria",10);
                POS_CURSOR(2,2);        //(pos y, pos x)
                ESCRIBE_MENSAJE("Mecatronica",11);
                break;
            case 2:
                POS_CURSOR(1,3);        //(pos y, pos x)
                ESCRIBE_MENSAJE("Ingenieria",10);
                POS_CURSOR(2,3);        //(pos y, pos x)
                ESCRIBE_MENSAJE("Biomedica",9);
                break;
        }
        INTCON0bits.GIE = 1;
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    if(estado == 2){
        estado = 0;
    }
    else{
        estado++;
    }
    BORRAR_LCD();
}

