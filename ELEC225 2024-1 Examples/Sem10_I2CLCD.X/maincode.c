#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB.UART.h"

#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
}

void splash_screen(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola mundo!");
    __delay_ms(1000);
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Electronica");
    __delay_ms(5000);
    I2C_BORRAR_LCD();
}

void main(void) {
    unsigned char contador=0;
    configuro();
    I2C_LCD_INIT();
    U1_INIT();
    splash_screen();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Contador: ");
        for(contador=0;contador<255;contador++){
            I2C_POS_CURSOR(2,0);
            I2C_ENVIA_LCD_DATA((contador / 100) + 0x30);        
            I2C_ENVIA_LCD_DATA(((contador % 100) / 10) + 0x30);
            I2C_ENVIA_LCD_DATA((contador % 10) + 0x30);
            __delay_ms(50);
        }
    }
}
