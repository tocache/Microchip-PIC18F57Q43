#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0;  //RC0 digital
    //configuracion de XXX
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(25);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servomon UPC",12);
    while(1){
        if(PORTBbits.RB4 == 0){
           LATCbits.LATC0 = 1;
           __delay_us(2500);
           LATCbits.LATC0 = 0;
           __delay_us(17500);
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("BTN:1 Servo:180",15);
            ENVIA_CHAR(0xDF);
        }
        else{
           LATCbits.LATC0 = 1;
           __delay_us(500);
           LATCbits.LATC0 = 0;
           __delay_us(19500);
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("BTN:0 Servo:000",15);
            ENVIA_CHAR(0xDF);
        }
    }
}
