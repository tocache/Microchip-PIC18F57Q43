#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISD = 0x0F;
    ANSELD = 0x0F;
    TRISE = 0xF8;
    ANSELE = 0xF8;
    LCD_INIT();
    //configuración del UART
    U1BRGH = 0x00;
    U1BRGL = 25;      //BRG=25 para 9600 baudios con BRGS=0
    //U3BRGS = 0;         //normal speed
    U1CON0 = 0x30;      //BRGS=0, TXEN=1, RXEN=1, MODE=00 (8bit async uart)
    RF0PPS = 0x20;       //asignación de RF0 para TX de UART1 
    U1RXPPS = 0x29;      //asignaci{on de RF1 para RX de UART1
    U1CON1 = 0x80;      // UART1 enabled
    U1CON2 = 0x00;      //por seacaso
    INTCON0bits.GIE = 1;
    PIE4bits.U1IE = 1;
    PIE4bits.U1RXIE = 1;
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
}

void UART1_Data_Send(unsigned char dato){
    U1TXB = dato;
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

void splash_screen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Laboratorio 3");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Ya fui me retiro");
}

void main(void) {
    configuro();
    while(1){
        splash_screen();
        UART1_String_Send("Ya fui me retiro");
        UART1_Data_Send(0x0A);
        UART1_Data_Send(0x0D);
        __delay_ms(2000);
    }
}

void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    if(U1RXB == 'E'){
        LATFbits.LATF3 = 1;
        UART1_String_Send("LED apagado");
        UART1_Data_Send(0x0A);
        UART1_Data_Send(0x0D);
    }
    else if(U1RXB == 'A'){
        LATFbits.LATF3 = 0;
        UART1_String_Send("LED encendido");
        UART1_Data_Send(0x0A);
        UART1_Data_Send(0x0D);
    }    
}