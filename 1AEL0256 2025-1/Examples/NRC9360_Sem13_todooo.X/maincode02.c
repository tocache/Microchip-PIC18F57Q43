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
    ANSELB = 0xEC;
    WPUB = 0x13;
    I2C_LCD_INIT();
    WS2812_INIT();
}

void pantallon(void){
    unsigned char x;
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Ejercicio Sem13");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Micro UPC 2025-1");
    __delay_ms(2000);
    I2C_BORRAR_LCD();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Test DHT11");
    for(x=0;x<4;x++){
        I2C_ENVIA_LCD_DATA('.');
        __delay_ms(200);
    }
    I2C_ESCRIBE_MENSAJE2("ok");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Test WS2812");        
    for(x=0;x<3;x++){
        I2C_ENVIA_LCD_DATA('.');
        __delay_ms(200);
    }
    I2C_ESCRIBE_MENSAJE2("ok");        
    __delay_ms(2000);        
    I2C_BORRAR_LCD();    
}

void main(void) {
    configuro();
    pantallon();
    while(1){
        while(PORTBbits.RB0 == 0){
            WS2812_DATA_SEND(127,0,0);
            I2C_POS_CURSOR(1,0);
            I2C_ESCRIBE_MENSAJE2("Color: Verde    ");
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("                ");
        }
        while(PORTBbits.RB1 == 0){
            WS2812_DATA_SEND(0,127,0);
            I2C_POS_CURSOR(1,0);
            I2C_ESCRIBE_MENSAJE2("Color: Rojo     ");
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("                ");
        }
        while(PORTBbits.RB4 == 0){
            WS2812_DATA_SEND(0,0,127);
            I2C_POS_CURSOR(1,0);
            I2C_ESCRIBE_MENSAJE2("Color: Azul     ");
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("                ");
        }
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp DHT: ");
        I2C_LCD_ESCRIBE_VAR_CHAR(DHT_GetTemp(DHT11), 2);
        I2C_LCD_CHAR_GRADO();
        __delay_ms(500);
        I2C_ENVIA_LCD_DATA('C');
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Humed DHT: ");
        I2C_LCD_ESCRIBE_VAR_CHAR(DHT_GetHumid(DHT11), 2);
        I2C_ESCRIBE_MENSAJE2("%RH");
        __delay_ms(500);
    }
}
