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
    TRISAbits.TRISA0 = 0;          //ra0 salida
    ANSELAbits.ANSELA0 = 0;       //ra0 digital
    TRISB = 0xF3;               //rb0 y rb1 entradas, rb2 y rb3 salidas
    ANSELB = 0xF0;              //rb0 al rb3 digitales
    TRISFbits.TRISF0 = 0;       //rf0 salida
    ANSELFbits.ANSELF0 = 0;     //rf0 digital
    TRISFbits.TRISF1 = 1;       //rf1 entrada
    ANSELFbits.ANSELF1 = 0;     //rf1 digital
    TRISD = 0x0F;               //rd4 al rd7 salidas
    ANSELD = 0x0F;              //rd4 al rd7 digitales
    TRISE = 0xF8;               //re0 al re2 salidas
    ANSELE = 0xF8;              //re0 al re2 digitales
    //configuracion de interrupciones
    WPUB = 0x03;                //habilitacion de pullup individuales en rb0 y rb1
    INTCON0bits.GIE = 1;        //global interrupt enabled
    PIE1bits.INT0IE = 1;        //INT0 enabled
    PIE6bits.INT1IE = 1;        //INT1 enabled
    INTCON0bits.INT0EDG = 0;    //falling edge para INT0
    INTCON0bits.INT1EDG = 1;    //falling edge para INT1
    //configuracion del UART1
    U1CON0bits.BRGS = 0;        //BRGS= 0 o sea normal rate
    U1BRGH = 0;
    U1BRGL = 25;                //vtx de 9600 baudios
    U1CON0bits.TXEN = 1;        //habilitador del transmisor
    U1CON1bits.ON = 1;          //serial port U1 ON
}

void EUSART_ByteSend(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void EUSART_StringSend(unsigned char *cadenasa){
    unsigned char tam;
    tam = strlen(cadenasa);
    unsigned char x;
    for(x=0;x<tam;x++){
        EUSART_ByteSend(cadenasa[x]);
    }
}

void EUSART_NewLine(void){
    U1TXB = 0x0A;
    while(U1ERRIRbits.TXMTIF == 0);
    U1TXB = 0x0D;
    while(U1ERRIRbits.TXMTIF == 0);
}


void main(void) {
    configuro();
    EUSART_StringSend("PIC18F45K50 arrancando...");
    EUSART_NewLine();
    while(1);
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    EUSART_StringSend("Hola mundo");
    EUSART_NewLine();
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    EUSART_StringSend("Microcontroladores 2023-1");
    EUSART_NewLine();
}
