#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

unsigned int resultado = 0;     //variable donde se alojara
                                //el resultado del ADC
unsigned int millar, centena, decena, unidad;

void configuro(void){
    //configuracion del reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    
    //Setup ADC
    ADCON0bits.FM = 1;      //right justify
    ADCON0bits.CS = 1;      //ADCRC Clock
    ADPCH = 0x00;           //RA0 is Analog channel
    TRISAbits.TRISA0 = 1;   //Set RA0 to input
    ANSELAbits.ANSELA0 = 1; //Set RA0 to analog
    ADCON0bits.ON = 1;      //Turn ADC On
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(15);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void convierte(unsigned int numero){
    millar = numero / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void){
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("ADC Canal 0",11);
    while(1){
        //aqui va el codigo de la aplicacion
        ADCON0bits.GO = 1; //Start conversion
        while(ADCON0bits.GO); //Wait for conversion done
        resultado = (ADRESH << 8) + ADRESL;
        convierte(resultado);
        POS_CURSOR(2,0);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}


