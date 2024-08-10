/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 12 de junio de 2024, 02:04 PM
 */
#include <xc.h>
#include <string.h>
#include "cabcezota.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion del UART
    U1BRGH = 0;
    U1BRGL = 207;           //UART1 a 9600 baudios
    U1CON0 = 0x30;          //TX enabled, RX enabled
    U1CON1 = 0x80;          //UART1 habilitado (enabled)
    U1CON2 = 0x00;          //Dejarlo valores por defecto
    RF0PPS = 0x20;          //RF0 esta conectado a UART1TX
    U1RXPPS = 0x29;         //RF1 esta conectado a UART1RX    
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void U1_STRING_SEND(const char *cadena)
{
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
}

void U1_NEWLINE(void){
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

void main(void) {
    configuro();
    I2C_LCD_INIT();
    while(1){
        U1_STRING_SEND("|----------------------|");
        U1_NEWLINE();
        U1_STRING_SEND("|                      |");
        U1_NEWLINE();
        U1_STRING_SEND("|     Hola mundo!      |");
        U1_NEWLINE();
        U1_STRING_SEND("|  Microcontroladores  |");
        U1_NEWLINE();
        U1_STRING_SEND("|                      |");
        U1_NEWLINE();
        U1_STRING_SEND("|----------------------|");
        U1_NEWLINE();
        U1_NEWLINE();
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Hola mundo!");
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("UPC 2024 Ingenieria");
        I2C_POS_CURSOR(3,0);
        I2C_ESCRIBE_MENSAJE2("Los pollitos dicen");
        I2C_POS_CURSOR(4,0);
        I2C_ESCRIBE_MENSAJE2("pio pio pio y pio");        
        __delay_ms(1000);
    }
}
