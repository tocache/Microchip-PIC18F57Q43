#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_WS2812.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    WS2812_INIT();
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Micro UPC Sem13");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("LED Neopixel");
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        WS2812_DATA_SEND(255,0,0);
        __delay_ms(50);
    }
}
