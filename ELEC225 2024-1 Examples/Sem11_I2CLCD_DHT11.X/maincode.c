/*
 * File:   maincode.c
 * Author: electronica
 *
 * Created on 3 de junio de 2024, 12:15 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "dht11_lib.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;
}

void splash_screen(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Inicializando el");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("termometro");
    unsigned char temp;
    for(temp=0;temp<6;temp++){
        I2C_ENVIA_LCD_DATA('.');
        __delay_ms(300);
    }
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    I2C_LCD_INIT();
    splash_screen();
    while(1){
        unsigned char RH_Ent, RH_Dec, Temp_Ent, Temp_Dec, Chksum;
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
        __delay_ms(1000);        
    }
}
