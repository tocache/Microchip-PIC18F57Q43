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

unsigned char cuenta = 0;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //configuracion de la INT1
    INT1PPS = 0x0C;     //RB4 con la INT1
    PIE6bits.INT1IE = 1;
    PIR6bits.INT1IF = 0;
    INTCON0bits.INT1EDG = 0;
    INTCON0bits.GIE = 1;
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
    __delay_ms(2000);
    BORRAR_LCD();
    while(1){
        unsigned char x_var;
        POS_CURSOR(1,0);    //y,x
        ESCRIBE_MENSAJE("Cuenta:", 7);
        ENVIA_CHAR((cuenta / 100) + 0x30);       //envio de centena
        ENVIA_CHAR(((cuenta % 100) / 10) + 0x30); //envio de decena
        ENVIA_CHAR((cuenta % 10) + 0x30);    //envio de unidad
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(cuenta == 128){
        cuenta = 0;
    }
    else{
        cuenta++;
    }
    __delay_ms(15);     //el antirrebote
}