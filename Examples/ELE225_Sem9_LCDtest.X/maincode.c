/*
 * File:   maincode.c
 * Author: Kalun Lau
 *
 * Created on 29 de mayo de 2023, 10:13 AM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del reloj principal
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
    TRISB = 0xFF;
    ANSELB = 0xFC;
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    //inicializacion del LCD
    LCD_INIT();
    LATCbits.LATC1 = 1;     //enciendo el backlight del LCD
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo!");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Con fe aprobare");
    while(1){
        DISPLAY_SHIFTRIGHT();
        __delay_ms(500);
        DISPLAY_SHIFTRIGHT();
        __delay_ms(500);
        DISPLAY_SHIFTRIGHT();
        __delay_ms(500);
        DISPLAY_SHIFTLEFT();
        __delay_ms(500);
        DISPLAY_SHIFTLEFT();
        __delay_ms(500);
        DISPLAY_SHIFTLEFT();
        __delay_ms(500);

    }
}
