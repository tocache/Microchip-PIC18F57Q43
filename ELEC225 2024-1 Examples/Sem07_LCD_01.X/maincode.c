#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;          //HFINTOSC a 16MHz
    OSCEN = 0x40;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    LATCbits.LATC0 = 1;     //para encender el backlight del LCD
}

void main(void) {
    configuro();
    LCD_INIT();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("HOLA MUNDO!");
    while(1){
        unsigned char x_var;
        for(x_var=0;x_var<100;x_var++){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("Cuenta:");
            LCD_ESCRIBE_VAR_CHAR(x_var,2);
            __delay_ms(200);
        }
    }
}
