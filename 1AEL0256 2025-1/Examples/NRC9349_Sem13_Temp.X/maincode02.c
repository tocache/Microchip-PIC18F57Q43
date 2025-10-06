#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#define _XTAL_FREQ 32000000UL

unsigned int temperatura_dht11, humedad_dht11;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
}

void main(void) {
    configuro();
    I2C_LCD_INIT();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola UPCino");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Micro 2025-1");
    __delay_ms(2000);
    I2C_BORRAR_LCD();
    while(1){
        temperatura_dht11 = DHT_GetTemp(DHT22);
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp DHT:");
        I2C_LCD_ESCRIBE_VAR_INT(temperatura_dht11/10, 2, 0);
        I2C_LCD_CHAR_GRADO();
        I2C_ENVIA_LCD_DATA('C');
        __delay_ms(1000);
        humedad_dht11 = DHT_GetHumid(DHT22);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humed DHT:");
        I2C_LCD_ESCRIBE_VAR_INT(humedad_dht11/10, 2, 0);
        I2C_ENVIA_LCD_DATA('%');
        __delay_ms(1000);        
    }
}