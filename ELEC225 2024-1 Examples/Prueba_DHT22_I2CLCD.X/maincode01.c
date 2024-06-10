/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 10 de junio de 2024, 04:46 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

unsigned int temperatura=0;
unsigned int humedad=0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
}

void splash_screen(void){
    __delay_ms(1000);
    U1_STRING_SEND("Ingenieria Electronica UPAO 2024");
    U1_NEWLINE();
    U1_STRING_SEND("Semana 12");
    U1_NEWLINE();
    U1_STRING_SEND("Taller de microcontroladores");
    U1_NEWLINE();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Electronica UPAO");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Taller de Micro");
    __delay_ms(2000);  
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    U1_INIT(BAUD_9600);
    I2C_LCD_INIT();
    splash_screen();
    while(1){
        temperatura = DHT_GetTemp(DHT22);
        __delay_ms(500);
        humedad = DHT_GetHumid(DHT22);
        __delay_ms(500);        
        U1_STRING_SEND("Temperatura DHT22: ");
        U1_VAR_INT(temperatura, 3, 1);
        U1_STRING_SEND("*C");                
        U1_NEWLINE();
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp: ");
        I2C_LCD_ESCRIBE_VAR_INT(temperatura, 3, 1);
        I2C_ENVIA_LCD_DATA(0xDF);
        I2C_ENVIA_LCD_DATA('C');        
        U1_STRING_SEND("Humedad DHT22: ");
        U1_VAR_INT(humedad, 3, 1);
        U1_STRING_SEND("% RH");                
        U1_NEWLINE();
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humid: ");
        I2C_LCD_ESCRIBE_VAR_INT(humedad, 3, 1);
        I2C_ESCRIBE_MENSAJE2("% RH");
    }
}
