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
#define UP 0
#define DOWN 1
#define LENTO 2
#define RAPIDO 3

unsigned int cuenta = 0;
unsigned char estado = UP;
unsigned char speed = LENTO;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    TRISBbits.TRISB2 = 1;
    ANSELBbits.ANSELB2 = 0;
    WPUBbits.WPUB2 = 1;
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSELB3 = 0;
    WPUBbits.WPUB3 = 1;
    //configuracion de las interrupciones
    INT0PPS = 0x0A;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    INTCON0bits.INT0EDG = 0;
    INT1PPS = 0x0B;
    PIE6bits.INT1IE = 1;
    PIR6bits.INT1IF = 0;
    INTCON0bits.INT1EDG = 0;
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

void visualizacion(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Cuenta:", 7);
    ENVIA_CHAR((cuenta / 1000) + 0x30);        //decena
    ENVIA_CHAR(((cuenta % 1000) / 100) + 0x30);        //unidad
    ENVIA_CHAR(((cuenta % 100) / 10) + 0x30);        //decena
    ENVIA_CHAR((cuenta % 10) + 0x30);        //unidad
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
        switch(estado){
            case UP:
                if(cuenta == 8001){
                    cuenta = 0;
                }
                else{
                    cuenta++;
                }
                break;
            case DOWN:
                if(cuenta == 0){
                    cuenta = 8000;
                }
                else cuenta--;
                break;
        }
        visualizacion();
        switch(speed){
            case LENTO:
                __delay_ms(200);
                break;
            case RAPIDO:
                __delay_ms(1);
                break;
        }
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(speed == LENTO){
        speed = RAPIDO;
    }
    else{
        speed = LENTO;
    }
    __delay_ms(50);    
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(estado == UP){
        estado = DOWN;
    }
    else{
        estado = UP;
    }
    __delay_ms(50);
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    cuenta = 0;
    __delay_ms(50);    
}
