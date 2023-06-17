#include <xc.h>
#include <string.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del oscilador interno
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISAbits.TRISA0 = 0;           //ra0 salida
    ANSELAbits.ANSELA0 = 0;         //ra0 digital
    TRISB = 0xF3;                   //rb0 y rb1 entradas, rb2 y rb3 salidas
    ANSELB = 0xF0;                  //rb0 al rb3 digitales
    TRISD = 0x0F;                   //rd4 al rd7 salidas
    ANSELD = 0x0F;                  //rd4 al rd7 digitales
    TRISE = 0xF8;                   //re0 al re2 salidas
    ANSELE = 0xF8;                  //re0 al re2 digitales
    TRISFbits.TRISF0 = 0;           //rf0 salida
    ANSELFbits.ANSELF0 = 0;         //rf0 digital
    TRISFbits.TRISF1 = 1;           //rf1 entrada
    ANSELFbits.ANSELF1 = 0;         //rf1 digital
    //interrupciones
    WPUB = 0x03;                    //pullup enabled para rb0 y rb1
    INTCON0bits.INT0EDG = 0;        //falling edge para INT0
    INTCON0bits.INT1EDG = 0;        //falling edge para INT1
    INTCON0bits.GIE = 1;            //global interrupt enabled
    PIE1bits.INT0IE = 1;            //INT0 enabled
    PIE6bits.INT1IE = 1;            //INT1 enabled
    //configuracion del UART
    U1CON0bits.BRGS = 0;            //normal rate
    U1BRGH = 0;
    U1BRGL = 25;                    //vtx 9600
    U1CON0bits.TXEN = 1;            //transmisor del uart1 enabled
    U1CON1bits.ON = 1;              //uart1 enabled
    RF0PPS = 0x20;                  //asignacion PPS de rf0 hacia uart1 tx
}

void EUSART_SendByte(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void EUSART_SendString(unsigned char *cadenasa){
    unsigned char tam;
    tam = strlen(cadenasa);
    unsigned char x;
    for(x=0;x<tam;x++){
        EUSART_SendByte(cadenasa[x]);
    }
}

void EUSART_NewLine(void){
    U1TXB = 0x0D;
    while(U1ERRIRbits.TXMTIF == 0);
    U1TXB = 0x0A;
    while(U1ERRIRbits.TXMTIF == 0);
}


void main(void) {
    configuro();
    while(1);
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    unsigned char x;
    for(x=0;x<50;x++){
        LATAbits.LATA0 = 1;
        __delay_us(700);
        LATAbits.LATA0 = 0;
        __delay_us(19300);
    }    
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    unsigned char x;
    for(x=0;x<50;x++){
        LATAbits.LATA0 = 1;
        __delay_us(2300);
        LATAbits.LATA0 = 0;
        __delay_us(17700);
    }    
}