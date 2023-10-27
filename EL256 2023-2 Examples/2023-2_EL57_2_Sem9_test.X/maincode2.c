#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISBbits.TRISB4 = 1;       //RB4 como entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 como digital
    WPUBbits.WPUB4 = 1;         //RB4 con pullup activadoa
    TRISFbits.TRISF3 = 0;       //RF3 como salida
    ANSELFbits.ANSELF3 = 0;     //RF3 como digital
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
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Parpadeador LED", 15);
    while(1){
        if(PORTBbits.RB4 == 0){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Parpadeo rapido", 15);
            LATFbits.LATF3 = 0;
            __delay_ms(50);
            LATFbits.LATF3 = 1;
            __delay_ms(50);
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Parpadeo lento ", 15);
            LATFbits.LATF3 = 0;
            __delay_ms(200);
            LATFbits.LATF3 = 1;
            __delay_ms(200);
        }
    }
}
