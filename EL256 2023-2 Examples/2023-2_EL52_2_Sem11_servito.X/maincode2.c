#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC divider 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;       //RB4 entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 digital (boton integrado)
    WPUBbits.WPUB4 = 1;         //RB4 pullup enabled
    TRISCbits.TRISC0 = 0;       //RC0 salida
    ANSELCbits.ANSELC0 = 0;     //RC0 digital (salida al servo)
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
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servito UPCino",14);
    while(1){
        if(PORTBbits.RB4 == 0){
            //verdad, servo a 180 grados
            LATCbits.LATC0 = 1;
            __delay_us(2300);
            LATCbits.LATC0 = 0;
            __delay_us(17700);
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Posicion: 180",13);
            ENVIA_CHAR(0xDF);
        }
        else{
            //falso, servo a 0 grados
            LATCbits.LATC0 = 1;
            __delay_us(700);
            LATCbits.LATC0 = 0;
            __delay_us(19300);
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Posicion: 000",13);
            ENVIA_CHAR(0xDF);
        }
    }
}
