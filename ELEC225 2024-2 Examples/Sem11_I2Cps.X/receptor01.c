/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 21 de octubre de 2024, 11:44 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

unsigned int temperatura[], humedad[];
unsigned char tramaserial[30];
unsigned char indice=0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    U1_INIT(BAUD_9600);
    //configuracion de las interrupciones
    PIE4bits.U1RXIE = 1;
    PIR4bits.U1RXIF = 0;
    INTCON0bits.GIE = 1;
}

void pantallazo(void){
    __delay_ms(500);
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Taller de Micro");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Semana 11");
    U1_STRING_SEND("Taller de Micro");
    U1_NEWLINE();
    U1_STRING_SEND("Semana 11");
    __delay_ms(2000);
    I2C_POS_CURSOR(1,0);
    I2C_BORRAR_LCD();    
    I2C_ESCRIBE_MENSAJE2("Test DHT22");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("I2C LCD Receptor");
    U1_NEWLINE();
    U1_STRING_SEND("Test DHT22");
    U1_NEWLINE();
    U1_STRING_SEND("I2C LCD Receptor");
    __delay_ms(2000);    
    I2C_BORRAR_LCD();   
}

void validacion_temp(void){
    unsigned char prueba=0;
    if(tramaserial[prueba] == 'T'){
        if(tramaserial[prueba+1] == 'e'){
            if(tramaserial[prueba+2] == 'm'){
                if(tramaserial[prueba+3] == 'p'){
                    if(tramaserial[prueba+4] == ':'){
                        if(tramaserial[prueba+5] == ' '){
                            temperatura[0] = tramaserial[prueba+6];
                            temperatura[1] = tramaserial[prueba+7];
                            temperatura[2] = tramaserial[prueba+8];
                            temperatura[3] = tramaserial[prueba+9];
                        }
                    }
                }
            }
        }
    }
    else{
        prueba++;
    }
}

void validacion_hum(void){
    unsigned char prueba=0;
    if(tramaserial[prueba] == 'H'){
        if(tramaserial[prueba+1] == 'u'){
            if(tramaserial[prueba+2] == 'm'){
                if(tramaserial[prueba+3] == 'i'){
                    if(tramaserial[prueba+4] == 'd'){
                        if(tramaserial[prueba+5] == ': '){
                            if(tramaserial[prueba+6] == ' '){
                                humedad[0] = tramaserial[prueba+7];
                                humedad[1] = tramaserial[prueba+8];
                                humedad[2] = tramaserial[prueba+9];
                                humedad[3] = tramaserial[prueba+10];
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        prueba++;
    }
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        validacion_temp();
        validacion_hum();
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp: ");
        unsigned char var_x;
        for(var_x=0;var_x<4;var_x++){
            I2C_ENVIA_LCD_DATA(temperatura[var_x]);
        }
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humid: ");
        for(var_x=0;var_x<5;var_x++){
            I2C_ENVIA_LCD_DATA(humedad[var_x]);
        }
    }
}

void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    if(tramaserial == 0xAA){
        indice = 0;
    }
    tramaserial[indice] = U1RXB;
    indice++;
}