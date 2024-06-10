#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

unsigned char pantalla = 0;
unsigned int ch0,ch1,ch2,ch3,vo0,vo1,vo2,vo3;
unsigned int temporal = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;          //HFINTOSC a 16MHz
    OSCEN = 0x40;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    LATCbits.LATC0 = 1;     //para encender el backlight del LCD
    //configuracion del ADC
    TRISA = 0xFF;
    ANSELA = 0xFF;          //RA0-3 como entradas analogicas
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADCON0bits.ADON = 1;    //ADC On
    //configuracion de INTs
    TRISB = 0xFF;           //RB0, RB1 y RB2 como entradas
    ANSELB = 0xFE;          //RB0, RB1 y RB2 como digitales
    WPUB = 0x01;            //RB0, RB1 y RB2 weakpullup activados
    INTCON0bits.INT0EDG = 0;    //INT0 flanco descendente
    PIE1bits.INT0IE = 1;        //INT0 habilitado
    INTCON0bits.GIE = 1;        //Global interrupt habilitado
}

unsigned int tomamuestra_ADC(unsigned char canal){
    ADPCH = canal;           //seleccion del canal analógico
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return ((ADRESH << 8) + ADRESL);
}

void adquiere(void){
    ch0 = tomamuestra_ADC(0);
    ch1 = tomamuestra_ADC(1);
    ch2 = tomamuestra_ADC(2);
    ch3 = tomamuestra_ADC(3);
    vo0 = ch0/82;
    vo1 = ch1/82;
    vo2 = ch2/82;
    vo3 = ch3/82;
}

void main(void) {
    configuro();
    LCD_INIT();
    while(1){
        adquiere();
        switch(pantalla){
            case 0:
                POS_CURSOR(1,0);
                ESCRIBE_MENSAJE2("C0:");
                LCD_ESCRIBE_VAR_INT(ch0,4);
                ESCRIBE_MENSAJE2(" C1:");
                LCD_ESCRIBE_VAR_INT(ch1,4);
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("C2:");
                LCD_ESCRIBE_VAR_INT(ch2,4);
                ESCRIBE_MENSAJE2(" C3:");
                LCD_ESCRIBE_VAR_INT(ch3,4);
                break;
            case 1:
                POS_CURSOR(1,0);
                ESCRIBE_MENSAJE2("V0:");
                LCD_ESCRIBE_VAR_INT(vo0/10,2);
                ENVIA_CHAR('.');
                LCD_ESCRIBE_VAR_INT(vo0%10,2);
                ENVIA_CHAR('V');
                ESCRIBE_MENSAJE2(" V1:");
                LCD_ESCRIBE_VAR_INT(vo1/10,2);
                ENVIA_CHAR('.');
                LCD_ESCRIBE_VAR_INT(vo1%10,2);
                ENVIA_CHAR('V');
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("V2:");
                LCD_ESCRIBE_VAR_INT(vo2/10,2);
                ENVIA_CHAR('.');
                LCD_ESCRIBE_VAR_INT(vo2%10,2);
                ENVIA_CHAR('V');
                ESCRIBE_MENSAJE2(" V3:");
                LCD_ESCRIBE_VAR_INT(vo3/10,2);
                ENVIA_CHAR('.');
                LCD_ESCRIBE_VAR_INT(vo3%10,2);
                ENVIA_CHAR('V');
                break;
        }
    }
}
//zona de atencion a las interrupciones
void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(pantalla == 1){
        pantalla = 0;
    }
    else{
        pantalla = 0;
    }
}

void __interrupt(irq(default)) default_ISR(void){
}