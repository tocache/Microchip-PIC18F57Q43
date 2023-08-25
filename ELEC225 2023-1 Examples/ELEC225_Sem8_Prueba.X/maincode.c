#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char humita[]={0x3F,0x30,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
unsigned int tamal = 4567;
unsigned millar, centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador interno}
    OSCCON1 = 0x60;     //HFINTOSC
    OSCFRQ = 0x02;      //HFINTOSC para 4MHz
    OSCEN = 0x40;       //HFINTOSC habilitado  
    //configuracion de E/S
    TRISC = 0x80;       //RC6 al RC0 como salidas
    ANSELC = 0x80;      //RC6 al RC0 como digitales
    TRISA = 0xF0;       //RA3 al RA0 como salidas
    ANSELA = 0xF0;      //RA3 al RA0 como digitales
    TRISB = 0xFF;       //RB2 al RB0 como entradas
    ANSELB = 0x00;      //RB2 al RB0 como digitales
    WPUB = 0x07;        //RB2 al RB0 con pull up activados
    //configuracion de las interrupciones
    INTCON0bits.GIE = 1;        //global
    INTCON0bits.INT0EDG = 0;    //falling edge para INT0
    INTCON0bits.INT1EDG = 0;    //falling edge para INT1
    INTCON0bits.INT2EDG = 0;    //falling edge para INT2
    PIE1bits.INT0IE = 1;        //INT0 habilitado
    PIE6bits.INT1IE = 1;        //INT1 habilitado
    PIE10bits.INT2IE = 1;       //INT2 habilitado
}

void convierte(unsigned int numero){
    millar = numero / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    LATA = 0xFF;
    while(1){
        convierte(tamal);
        LATC = humita[millar];
        LATAbits.LATA3 = 0;
        __delay_ms(1);
        LATAbits.LATA3 = 1;
        LATC = humita[centena];
        LATAbits.LATA2 = 0;
        __delay_ms(1);
        LATAbits.LATA2 = 1;
        LATC = humita[decena];
        LATAbits.LATA1 = 0;
        __delay_ms(1);
        LATAbits.LATA1 = 1;
        LATC = humita[unidad];
        LATAbits.LATA0 = 0;
        __delay_ms(1);
        LATAbits.LATA0 = 1;
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(tamal == 9999){
        tamal = 0;
    }
    else{
        tamal++;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(tamal == 0){
        tamal = 9999;
    }
    else{
        tamal--;
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    tamal = 0;
}
