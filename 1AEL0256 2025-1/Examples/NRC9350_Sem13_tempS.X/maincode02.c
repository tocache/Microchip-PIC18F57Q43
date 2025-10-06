#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#define _XTAL_FREQ 32000000UL

volatile unsigned char cuenta = 0;
volatile unsigned int dht_temp, dht_humid;

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
        I2C_ESCRIBE_MENSAJE2("Temp DHT:");
        dht_temp = DHT_GetTemp(DHT22);
        I2C_LCD_ESCRIBE_VAR_INT(dht_temp/10, 2, 0);
        I2C_LCD_CHAR_GRADO();
        I2C_ENVIA_LCD_DATA('C');
        __delay_ms(1000);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humid DHT:");
        dht_humid = DHT_GetHumid(DHT22);
        I2C_LCD_ESCRIBE_VAR_INT(dht_humid/10, 2, 0);
        I2C_ESCRIBE_MENSAJE2("%RH");
        __delay_ms(1000);        
    }
}
