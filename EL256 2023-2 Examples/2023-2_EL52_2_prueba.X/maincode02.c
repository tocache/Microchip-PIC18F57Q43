#include <xc.h>
#include "cabecera.h"
#include "LCD.h"

#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;         //HFINTOSC, POSTS 1:1
    OSCFRQ = 0x07;          //HFINTOSC a 48MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup activado
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
}

void lcd_init(void){
    TRISD = 0x00;           //RD como salida
    ANSELD = 0x00;          //RD como digital
    LCD_CONFIG();
    __delay_ms(23);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Hola mundo UPC!", 15);
    while(1){
        if(PORTBbits.RB4 == 0){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Modo: Rapidisimo", 16);
            LATBbits.LATB0 = 1;
            __delay_ms(100);
            LATBbits.LATB0 = 0;
            __delay_ms(100);
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Modo: Lentisimo ", 16);
            LATBbits.LATB0 = 1;
            __delay_ms(300);
            LATBbits.LATB0 = 0;
            __delay_ms(300);
        }
    }
}
