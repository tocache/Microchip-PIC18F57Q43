#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char millar, centena, decena, unidad;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISD = 0x0F;
    ANSELD = 0x0F;
    TRISA = 0xF8;
    ANSELA = 0xF8;
    TRISB = 0xFF;
    ANSELB = 0xFC;
    WPUB = 0x03;
    INTCON0bits.INT0EDG = 0;
    INTCON0bits.INT1EDG = 0;
    INTCON0bits.GIE = 1;
    PIE1bits.INT0IE = 1;
    PIE6bits.INT1IE = 1;
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADCON0bits.ADON = 1;      //ADC On
    LCD_INIT();
}

void convierte(unsigned int numero){
    millar = numero / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

unsigned int tomamuestra_ADC(unsigned char canal){
    ADPCH = canal;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH<<8) + ADRESL;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Laboratorio 3");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Estoy jaladaso:(");
    __delay_ms(4000);
    BORRAR_LCD();
    while(1){
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("C3:");
        convierte(tomamuestra_ADC(3));
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ESCRIBE_MENSAJE2(" C5:");
        convierte(tomamuestra_ADC(5));
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("C6:");
        convierte(tomamuestra_ADC(6));
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    BORRAR_LCD();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Laboratorio 3");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Microbio 2023");
    __delay_ms(5000);
    BORRAR_LCD();
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    BORRAR_LCD();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Kalun Jose");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2(" Lau Gan");
    __delay_ms(5000);
    BORRAR_LCD();
}