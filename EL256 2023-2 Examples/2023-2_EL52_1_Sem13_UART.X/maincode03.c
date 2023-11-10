#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;             //HFINTOSC DIV 1:1
    OSCFRQ = 0x06;              //HFINTOSC a 32MHz
    OSCEN = 0x40;               //HFINTOSC enabled
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;       //RA0 entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 analogica
    TRISBbits.TRISB0 = 1;       //RB0 entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 digital
    WPUBbits.WPUB0 = 1;         //RB0 pullup enabled
    TRISBbits.TRISB1 = 1;       //RB1 entrada
    ANSELBbits.ANSELB1 = 0;     //RB1 digital
    WPUBbits.WPUB1 = 1;         //RB1 pullup enabled
    TRISCbits.TRISC0 = 0;       //RC0 salida
    ANSELCbits.ANSELC0 = 0;     //RC0 digital
    LATCbits.LATC0 = 0;         //RC0 en cero
    TRISCbits.TRISC1 = 0;       //RC1 salida
    ANSELCbits.ANSELC1 = 0;     //RC1 digital
    LATCbits.LATC1 = 0;         //RC1 en cero
    TRISFbits.TRISF0 = 0;       //RF0 salida
    ANSELFbits.ANSELF0 = 0;     //RF0 digital
    TRISFbits.TRISF1 = 1;       //RF1 entrada
    ANSELFbits.ANSELF1 = 0;     //RF1 digital
    //configuracion del UART1
    U1BRGH = 0;
    U1BRGL = 207;               //BRG trabajando a 9600 baudios con BRGS=0
    U1CON0 = 0x30;              //BRGS=0 TX enabled, RX enabled, async bit UART
    U1CON1 = 0x80;              //UART1 enabled
    U1CON2 = 0x00;              //valores por defecto
    RF0PPS = 0x20;              //RF0 esta conectado al UART1-TX
    U1RXPPS = 0x29;             //RF1 esta conectado al UART1-RX
    PIE4bits.U1RXIE = 1;        //interrupcion de RX de UART1 habilitado
    PIR4bits.U1RXIF = 0;        //bajamos bandera de RX de UART1
    INTCON0bits.GIE = 1;        //habilitador global de interrupts enabled
    //configuracion del display 16x2
    LCD_INIT();
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void U1_NEW_LINE(void){
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

void U1_STRING_SEND(const char *cadena){
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("EL52-1 Sem13");
    U1_STRING_SEND("Hola mundo mundial");
    U1_NEW_LINE();
    unsigned char x;
    for(x=0;x<=16;x++){
        POS_CURSOR(2,(16-x));
        ESCRIBE_MENSAJE2("Microcontrolador");
        __delay_ms(300);
    }
    while(1){        
    }
}

void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;        //bajamos bandera de RX de UART1
    switch(U1RXB){
        case 'Q':
            LATCbits.LATC0 = 1;
            U1_STRING_SEND("LED0 encendido");
            U1_NEW_LINE();
            break;
        case 'W':
            LATCbits.LATC0 = 0;
            U1_STRING_SEND("LED0 apagado");
            U1_NEW_LINE();
            break;
        case 'A':
            LATCbits.LATC1 = 1;
            U1_STRING_SEND("LED1 encendido");
            U1_NEW_LINE();
            break;
        case 'S':
            LATCbits.LATC1 = 0;
            U1_STRING_SEND("LED1 apagado");
            U1_NEW_LINE();
            break;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void)
{
// Unhandled interrupts go here
}
