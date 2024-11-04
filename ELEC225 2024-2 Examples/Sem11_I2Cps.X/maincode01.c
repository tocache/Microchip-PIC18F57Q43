/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 21 de octubre de 2024, 11:44 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
//#include "dht11_lib.h"
#define _XTAL_FREQ 32000000UL

unsigned int temperatura, humedad;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
}

void pantallazo(void){
    __delay_ms(500);
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Taller de Micro");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Semana 11");
    __delay_ms(2000);
    I2C_POS_CURSOR(1,0);
    I2C_BORRAR_LCD();    
    I2C_ESCRIBE_MENSAJE2("Test DHT22");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("I2C LCD");
    __delay_ms(2000);    
    I2C_BORRAR_LCD();    
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
/*        unsigned char RH_Ent, RH_Dec, Temp_Ent, Temp_Dec, Chksum;
        DHT11_Start();
        DHT11_Check();
        RH_Ent = DHT11_Read();
        RH_Dec = DHT11_Read();
        Temp_Ent = DHT11_Read();
        Temp_Dec = DHT11_Read();
        Chksum = DHT11_Read();
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp:");
        I2C_LCD_ESCRIBE_VAR_CHAR(Temp_Ent, 2);
        I2C_ENVIA_LCD_DATA(0xDF);
        I2C_ESCRIBE_MENSAJE2("C RH:");
        I2C_LCD_ESCRIBE_VAR_CHAR(RH_Ent, 2);
        I2C_ENVIA_LCD_DATA('%');
        __delay_ms(1000); */
        temperatura = DHT_GetTemp(DHT22);
        __delay_ms(500);
        humedad = DHT_GetHumid(DHT22);
        __delay_ms(500);        
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp: ");
        I2C_LCD_ESCRIBE_VAR_INT(temperatura, 3, 1);
        I2C_ENVIA_LCD_DATA(0xDF);
        I2C_ENVIA_LCD_DATA('C');        
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humid: ");
        I2C_LCD_ESCRIBE_VAR_INT(humedad, 3, 1);
        I2C_ESCRIBE_MENSAJE2("% RH");
    }
}
