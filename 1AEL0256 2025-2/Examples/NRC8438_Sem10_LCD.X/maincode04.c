/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 27 de octubre de 2025, 06:01 PM
 */
#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

const unsigned char carita_feliz[] = {0x00, 0x1B, 0x1B, 0x00,
                    0x04, 0x00, 0x11, 0x0E};
const unsigned char carita_triste[] = {0x00, 0x1B, 0x1B, 0x00,
                    0x04, 0x00, 0x0E, 0x11};
const unsigned char carita_meh[] = {0x00, 0x1B, 0x09, 0x00,
                    0x04, 0x00, 0x0E, 0x00};
unsigned int resultado_ADC;

void configuracion(void){
    //conf modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //conf las E/S
    ANSELB = 0xE7;  //RB3 y RB4 digitales
    WPUB = 0x18;    //RB3 y RB4 pullup enabled
    //conf las interrupciones
    INT0PPS = 0x0B; //INT0 proviene de RB3
    INT1PPS = 0x0C; //INT1 proviene de RB4
    PIE1bits.INT0IE = 1;    //INT0 enabled
    PIE6bits.INT1IE = 1;    //INT1 enabled
    PIR1bits.INT0IF = 0;    //INT0 flag en cero
    PIR6bits.INT1IF = 0;    //INT1 flag abajo
    INTCON0bits.GIE = 1;    //GIE enabled
    INTCON0bits.INT0EDG = 0;    //INT0 falling edge
    INTCON0bits.INT1EDG = 0;    //INT1 falling edge
    //conf del ADC
    ADCON0bits.ADFM = 1;    //adc just derecha
    ADCON0bits.ADCS = 1;    //clk source ADRC
    ADPCH = 0x00;           //canal a leer RA0/ANA0
    ADCON0bits.ADON = 1;    //adc on
}

void LCD_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    __delay_ms(17);
    LCD_CONFIG();
    __delay_ms(18);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(carita_feliz,0);
    GENERACARACTER(carita_triste,1);
    GENERACARACTER(carita_meh,2);
}

void main(void) {
    configuracion();
    LCD_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Hola Mundo UPC!",15);
    POS_CURSOR(2,8);
    /*ESCRIBE_MENSAJE(":)", 2);*/
   /*ENVIA_CHAR(0);
    ENVIA_CHAR(1);*/
    ENVIA_CHAR(2);
    ENVIA_CHAR(2);
    while(1){
        ADCON0bits.GO = 1;      //toma una muestra ADC
        while(ADCON0bits.GO == 1);  //espera a que termine de convertir
        resultado_ADC = (ADRESH << 8) + ADRESL;
        INTCON0bits.GIE = 0;
        POS_CURSOR(2,0);
        ENVIA_CHAR((resultado_ADC / 1000) + 0x30);  //sale el millar
        ENVIA_CHAR(((resultado_ADC % 1000) / 100) + 0x30); //sale la centena
        ENVIA_CHAR(((resultado_ADC % 100) / 10) + 0x30);   //sale la decena
        ENVIA_CHAR((resultado_ADC % 10) + 0x30);    //sale la unidad
        INTCON0bits.GIE = 1;        
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    POS_CURSOR(2,8);
    ENVIA_CHAR(0);
    ENVIA_CHAR(0);
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    POS_CURSOR(2,8);
    ENVIA_CHAR(1);
    ENVIA_CHAR(1);
}