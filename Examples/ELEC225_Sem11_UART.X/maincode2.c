#include <xc.h>
#include <string.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    U1BRGH = 00;
    U1BRGL = 25;      //BRG=25 para 9600 baudios con BRGS=0
    U1CON0 = 0x30;      //BRGS=0, TXEN=1, RXEN=0, MODE=00 (8bit async uart)
    RF0PPS = 0x20;       //asignación de RF0 para TX de UART1 
    U1CON2 = 0x00;
    U1CON1 = 0x80;      // UART1 enabled
    U1RXPPS = 0x29;      //asignacion de RF1 para RX de UART1
    TRISFbits.TRISF1 = 1;   //RF1 entrada
    ANSELFbits.ANSELF1 = 0; //RF1 digital
    PIE4bits.U1RXIE = 1;    //recepcion del UART1 interrupcion habilitado
    INTCON0bits.GIE = 1;    //interruptor global de inerrupciones habilitado
    INTCON0bits.INT0EDG = 0;//flanco negativo para INT0
    PIE1bits.INT0IE = 1;    //interrupcion externa INT0 habilitado
    INT0PPS = 0x0C;     //asignacion de RB4 para INT0
}

void UART1_Data_Send(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void UART1_NewLine(void){
    U1TXB = 0x0A;
    while(U1ERRIRbits.TXMTIF == 0);
    U1TXB = 0x0D;
    while(U1ERRIRbits.TXMTIF == 0);
}

void UART1_String_Send(const char *cadena)
{
	unsigned char tam;
    unsigned char i = 0;
    tam = strlen(cadena);
	for(i = 0; i<tam; i++)
	{
        U1TXB = cadena[i];
        while(U1ERRIRbits.TXMTIF == 0);
	}
}

void main(void) {
    configuro();
    while(1){
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    UART1_String_Send("Machucaste BTN wean");
    UART1_NewLine();
}

void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    if(U1RXB == 'A'){
        LATFbits.LATF3 = 0;
        UART1_String_Send("Machucaste A");
        UART1_NewLine();
    }
    else if(U1RXB == 'B'){
        LATFbits.LATF3 = 1;
        UART1_String_Send("Machucaste B");
        UART1_NewLine();
    }
    else if(U1RXB == 'C'){
        UART1_String_Send("Machucaste C");
        UART1_NewLine();
    }
    else{
        UART1_String_Send("Tecla errada, intente de nuevo weon");
        UART1_NewLine();
    }
}

