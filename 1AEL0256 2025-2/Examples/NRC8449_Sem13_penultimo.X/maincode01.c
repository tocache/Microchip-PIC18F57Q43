/*
 * File:   maincode01.c
 * Author: Alumnos
 *
 * Created on 21 de noviembre de 2025, 03:32 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //con modulo oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inicializacion de librerias
    I2C_LCD_INIT();
    U1_INIT(BAUD_9600);
}

void splash_screen(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola mundo PAPU");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Microbios 20252");
    I2C_POS_CURSOR(2,0);
    unsigned char x_var;
    for(x_var=0;x_var<16;x_var++){
        I2C_ENVIA_LCD_DATA(' ');
        __delay_ms(100);
    }
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

unsigned int cuenta=0;

void main(void) {
    configuro();
    splash_screen();
    while(1){
        struct DHT_Values medidas = DHT_GetBoth(DHT11);
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp:");
        I2C_LCD_ESCRIBE_VAR_INT(medidas.DHT_Temp, 2, 0);
        I2C_LCD_CHAR_GRADO();
        I2C_ESCRIBE_MENSAJE2("C ");
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humed:");
        I2C_LCD_ESCRIBE_VAR_INT(medidas.DHT_Humid, 2, 0);
        I2C_ESCRIBE_MENSAJE2("%RH ");        
        U1_STRING_SEND("********************");
        U1_NEWLINE();
        U1_STRING_SEND("* HOLA PAPU UPCINO *");
        U1_NEWLINE();
        U1_STRING_SEND("* PROFE AYUDE PEEE *");
        U1_NEWLINE();
        U1_STRING_SEND("*                  *");
        U1_NEWLINE();
        U1_STRING_SEND("* VEZ: ");
        U1_VAR_INT(cuenta,5,0);
        U1_STRING_SEND("       *");        
        U1_NEWLINE();
        U1_STRING_SEND("* TEMP: ");
        U1_VAR_INT(medidas.DHT_Temp,2,0);
        U1_STRING_SEND(" *C      *");        
        U1_NEWLINE();
        U1_STRING_SEND("* HUM: ");
        U1_VAR_INT(medidas.DHT_Humid,2,0);
        U1_STRING_SEND(" %RH      *");        
        U1_NEWLINE();
        U1_STRING_SEND("********************");
        U1_NEWLINE();
        U1_NEWLINE();
        cuenta++;
        __delay_ms(2000);
    }
}
