#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

const unsigned char persona_1[]={0x06,0x06,0x04,0x0D,
                                0x16,0x04,0x0A,0x1A};
const unsigned char persona_2[]={0x0C,0x0C,0x05,0x0E,
                                0x14,0x04,0x0A,0x13};
void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    //configuracion de la INT2
    INT2PPS = 0x0C;
    PIE10bits.INT2IE = 1;
    PIR10bits.INT2IF = 0;
    INTCON0bits.INT2EDG = 0;
    INTCON0bits.GIE = 1;
}

void lcd_init(){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(21);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(persona_1, 0);
    GENERACARACTER(persona_2, 1);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,1);        //POS(Y,X)
    ESCRIBE_MENSAJE("Micros 2025-1", 13);
    POS_CURSOR(2,0);        //POS(Y,X)
    ESCRIBE_MENSAJE("UPcinos Corazon", 15);
    __delay_ms(2000);
    BORRAR_LCD();
    while(1){
        POS_CURSOR(1,0);        //POS(Y,X)
        ENVIA_CHAR(0);
        __delay_ms(500);
        POS_CURSOR(1,0);        //POS(Y,X)
        ENVIA_CHAR(1);
        __delay_ms(500);        
    }
    
}
