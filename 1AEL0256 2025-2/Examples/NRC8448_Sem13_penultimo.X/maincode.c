/*
 * File:   maincode.c
 * Author: Alumnos
 *
 * Created on 21 de noviembre de 2025, 09:39 AM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_UART.h"

#define _XTAL_FRQ 32000000UL

void configuro(void){
    //conf mod oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inic de librerias
    I2C_LCD_INIT();
    U1_INIT(BAUD_9600);
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola mundo UPC!");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Microbios 202520");
    U1_STRING_SEND("Profe apruebeme ya pe!");
    U1_NEWLINE();
    __delay_ms(4000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        struct DHT_Values actuales = DHT_GetBoth(DHT11);
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp:");
        I2C_LCD_ESCRIBE_VAR_INT(actuales.DHT_Temp, 2, 0);
        I2C_LCD_CHAR_GRADO();
        I2C_ESCRIBE_MENSAJE2("C ");
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humed:");
        I2C_LCD_ESCRIBE_VAR_INT(actuales.DHT_Humid, 2, 0);
        I2C_ESCRIBE_MENSAJE2("%RH ");
        __delay_ms(2000);
    }
}
