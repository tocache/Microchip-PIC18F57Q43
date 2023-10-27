#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;          //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;       //RB4 entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 digital
    WPUBbits.WPUB4 = 1;         //RB4 con pullup activado
    TRISCbits.TRISC0 = 0;       //RC0 salida
    ANSELCbits.ANSELC0 = 1;     //RC0 digital
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(22);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servo UPCino", 12);
    while(1){
        if(PORTBbits.RB4 == 0){
            LATCbits.LATC0 = 1;
            __delay_us(500);
            LATCbits.LATC0 = 0;
            __delay_us(19500);
        }
        else{
            LATCbits.LATC0 = 1;
            __delay_us(2500);
            LATCbits.LATC0 = 0;
            __delay_us(17500);
        }
    }
}
