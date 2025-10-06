#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

volatile unsigned char cuenta = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
}

void main(void) {
    configuro();
    I2C_LCD_INIT();
    I2C_POS_CURSOR(1,1);
    I2C_ESCRIBE_MENSAJE2("Hello UPCino!");
    I2C_POS_CURSOR(2,1);
    I2C_ESCRIBE_MENSAJE2("Elec Meca Bio");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Contador:");
        I2C_LCD_ESCRIBE_VAR_CHAR(cuenta, 3);
        __delay_ms(100);
        cuenta++;
    }
}
