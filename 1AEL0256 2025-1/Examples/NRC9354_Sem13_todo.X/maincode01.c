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
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Micro UPC Sem13");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Termometro DHT");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp DHT:");
        I2C_LCD_ESCRIBE_VAR_CHAR(DHT_GetTemp(DHT11),2);
        I2C_LCD_CHAR_GRADO();
        I2C_ENVIA_LCD_DATA('C');
        __delay_ms(1000);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humed DHT:");
        I2C_LCD_ESCRIBE_VAR_CHAR(DHT_GetHumid(DHT11),2);
        I2C_ESCRIBE_MENSAJE2("%RH");
        __delay_ms(1000);    
    }
}
