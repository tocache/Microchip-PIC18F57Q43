/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 21 de octubre de 2024, 11:44 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 64000000UL

unsigned int tiempo = 0;
float temporal;
unsigned int final;
unsigned int termistor;

void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x08;  //HFINTOSC a 64MHz
    OSCEN = 0x40;
    //conf de las E/S
    TRISBbits.TRISB0 = 0;
    ANSELBbits.ANSELB0 = 0; //puerto TRIG del HCSR04
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0; //puerto ECHO del HCSR04
    //conf del ADC
    TRISAbits.TRISA1 = 1;   //RA1 entrada
    ANSELAbits.ANSELA1 = 1; //RA1 analogica
    ADCON0 = 0x94;  //ADC conv manual, ADCRC, just der, ADC on
    //conf del I2CLCD
    I2C_LCD_INIT();
}

void pantallazo(void){
    __delay_ms(500);
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Taller de Micro");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Semana 12");
    __delay_ms(2000);
    I2C_POS_CURSOR(1,0);
    I2C_BORRAR_LCD();    
    I2C_ESCRIBE_MENSAJE2("Test HCSR04");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("I2C LCD");
    __delay_ms(2000);    
    I2C_BORRAR_LCD();    
}

unsigned int leer_ADC(unsigned char canal){
    ADPCH = canal;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return((ADRESH<<8)+ADRESL);
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        LATBbits.LATB0 = 1;
        __delay_us(10);
        LATBbits.LATB0 = 0;
        while(PORTBbits.RB1 == 0);
        tiempo = 0;
        while(PORTBbits.RB1 == 1){
            tiempo++;
            __delay_us(1);
        }
        //calculo de la distancia
    	temporal = 0.034 * (tiempo / 2); //el valor de la distancia en cm
        final = temporal;
        //lectura del termistor NTC 10K
        termistor = leer_ADC(1);
        //visualizacion en el I2CLCD
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Dist: ");
        I2C_LCD_ESCRIBE_VAR_INT(final, 5, 0);
        I2C_ENVIA_LCD_DATA('c');
        I2C_ENVIA_LCD_DATA('m');        
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Term: ");
        I2C_LCD_ESCRIBE_VAR_INT(termistor, 4, 0);
    }
}
