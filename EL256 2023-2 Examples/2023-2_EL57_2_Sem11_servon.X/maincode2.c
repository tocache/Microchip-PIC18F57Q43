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

void delaymon(unsigned int valor){
    unsigned int x;
    for(x=0;x<valor;x++){
        __delay_us(10);
    }
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servomon UPC",12);
    while(1){
        unsigned char y;
        for(y=0;y<160;y++){
           LATCbits.LATC0 = 1;
           delaymon(y+50);
           LATCbits.LATC0 = 0;
           delaymon(2000-(y+50));
           POS_CURSOR(2,0);
           ESCRIBE_MENSAJE("Moviendo a 180",14);
           ENVIA_CHAR(0xDF);
        }
        for(y=160;y>0;--y){
           LATCbits.LATC0 = 1;
           delaymon(y+50);
           LATCbits.LATC0 = 0;
           delaymon(2000-(y+50));
           POS_CURSOR(2,0);
           ESCRIBE_MENSAJE("Moviendo a 000",14);
           ENVIA_CHAR(0xDF);
        }
    }
}
