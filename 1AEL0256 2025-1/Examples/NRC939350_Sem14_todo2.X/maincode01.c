#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
}

void splash_screen(void){
    unsigned char x_var;
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2(" NRC9350 Micro ");    
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Loading");
    for(x_var=0;x_var<7;x_var++){
        I2C_ENVIA_LCD_DATA('.');
        __delay_ms(300);
    }
    I2C_ESCRIBE_MENSAJE2("ok");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    splash_screen();
    while(1);
}
