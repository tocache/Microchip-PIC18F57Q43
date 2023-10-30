//esto es una prueba de proyecto usando el entorno MPLAB Xpress IDE

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int lectura_adc = 0;
float temporal = 0;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;
    OSCEN = 0x40;
    RF3PPS = 0x15;
    //configuracion del PWM
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
    T2PR = 250;
    CCP1CON = 0x9C;
    CCPR1H = 0;
    CCPR1L = 0;
    T2CON = 0xA0;
    T2CLKCON = 0x01;
    LCD_INIT();
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On        
}

void tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("LED Heart UPC");    
    while(1){
        tomamuestra_ADC();
        //ADRESH:ADRESL
        unsigned char x;
        for(x=0;x<=250;x+=5){
            CCPR1H = 250-x;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("DC:"); 
            LCD_ESCRIBE_VAR_CHAR(CCPR1H, 3);
            tomamuestra_ADC();
            lectura_adc = (ADRESH << 8) + ADRESL;
            ESCRIBE_MENSAJE2(" ADCH:");             
            LCD_ESCRIBE_VAR_INT(lectura_adc,4);
            __delay_ms(5);
        }
        for(x=0;x<=250;x+=5){
            CCPR1H = x;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("DC:"); 
            LCD_ESCRIBE_VAR_CHAR(CCPR1H, 3);
            tomamuestra_ADC();
            lectura_adc = (ADRESH << 8) + ADRESL;
            ESCRIBE_MENSAJE2(" ADCH:");             
            LCD_ESCRIBE_VAR_INT(lectura_adc,4);
            __delay_ms(5);
        }        
    }
}