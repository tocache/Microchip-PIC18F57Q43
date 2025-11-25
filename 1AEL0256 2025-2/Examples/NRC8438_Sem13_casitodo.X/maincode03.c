/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 17 de noviembre de 2025, 05:31 PM
 */
#include <xc.h>
#include <stdio.h>
#include "cabecera.h"
#include "LIB_UART.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#define _XTAL_FREQ 32000000UL

unsigned int Temperatura, Humedad;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inicializacion de modulos
    U1_INIT(BAUD_9600);
    I2C_LCD_INIT();
}

void main(void) {
    configuro();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola Mundo!");
    I2C_POS_CURSOR(2,1);
    I2C_ESCRIBE_MENSAJE2("Curiosity Nano");
    U1_STRING_SEND("Hola Mundo!");
    U1_NEWLINE();
    U1_STRING_SEND("Apuren que nos quedamos sin tiempo!");
    U1_NEWLINE();        
    __delay_ms(4000);
    I2C_BORRAR_LCD();
    while(1){
        struct DHT_Values actuales = DHT_GetBoth(DHT11);
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp: ");
        I2C_LCD_ESCRIBE_VAR_INT(actuales.DHT_Temp, 2, 0);
        I2C_LCD_CHAR_GRADO();
        I2C_ESCRIBE_MENSAJE2("C");
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humid: ");
        I2C_LCD_ESCRIBE_VAR_INT(actuales.DHT_Humid, 2, 0);
        I2C_ESCRIBE_MENSAJE2("%RH");
        U1_STRING_SEND("Temperatura del DHT11: ");
        U1_VAR_INT(actuales.DHT_Temp, 2, 0);
        U1_STRING_SEND(" *C");
        U1_NEWLINE();
        U1_STRING_SEND("Humedad del DHT11: ");
        U1_VAR_INT(actuales.DHT_Humid, 2, 0);
        U1_STRING_SEND(" %RH");
        U1_NEWLINE();                
        __delay_ms(1000);
    }
}
