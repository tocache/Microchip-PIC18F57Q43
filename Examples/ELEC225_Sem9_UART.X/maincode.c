#include <xc.h>
#include <string.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion del oscilador interno
    OSCCON1 = 0x60;     //HFINTOSC postscaler 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuración del UART
    U1BRGH = 0x00;
    U1BRGL = 25;      //BRG=25 para 9600 baudios con BRGS=0
    //U3BRGS = 0;         //normal speed
    U1CON0 = 0x30;      //BRGS=0, TXEN=1, RXEN=0, MODE=00 (8bit async uart)
    RF0PPS = 0x20;       //asignación de RF0 para TX de UART1 
    U1CON1 = 0x80;      // UART1 enabled
    U1CON2 = 0x00;      //por seacaso
}

void UART1_Data_Send(unsigned char dato){
    U1TXB = dato;
    while(U3ERRIRbits.TXMTIF == 0);
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
        UART1_String_Send("Hola mundo");
        //UART1_Data_Send('H');
        __delay_ms(1000);
    }
}
