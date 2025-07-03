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
    WS2812_INIT();
}

void main(void) {
    configuro();
    while(1){
        WS2812_DATA_SEND(255, 0, 0);
        __delay_ms(500);
        WS2812_DATA_SEND(0, 255, 0);
        __delay_ms(500);
        WS2812_DATA_SEND(0, 0, 255);
        __delay_ms(500);
        WS2812_DATA_SEND(255, 255, 0);
        __delay_ms(500);
        WS2812_DATA_SEND(0, 255, 255);
        __delay_ms(500);
        WS2812_DATA_SEND(255, 0, 255);
        __delay_ms(500);
        WS2812_DATA_SEND(255, 255, 255);
        __delay_ms(500);
    }
}
