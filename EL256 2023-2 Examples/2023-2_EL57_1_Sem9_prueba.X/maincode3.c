#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion del reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISFbits.TRISF3 = 0;   //RF3 como salida
    ANSELFbits.ANSELF3 = 0; //RF3 como digital
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup activado
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(15);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void){
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Kalun Lau Gan",13);
    while(1){
        //aqui va el codigo de la aplicacion
        if(PORTBbits.RB4 == 0){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Parpadeo rapido",15);
            //parpadeo rapido
            LATFbits.LATF3 = 1;     //enciendo LED
            __delay_ms(100);
            LATFbits.LATF3 = 0;     //apago LED
            __delay_ms(100);
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Parpadeo lento ",15);
            //parpadeo lento
            LATFbits.LATF3 = 1;     //enciendo LED
            __delay_ms(200);
            LATFbits.LATF3 = 0;     //apago LED
            __delay_ms(200);
        }        
    }
}

