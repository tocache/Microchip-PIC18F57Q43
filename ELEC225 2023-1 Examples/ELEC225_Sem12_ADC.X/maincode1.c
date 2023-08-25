#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char diezmillar,millar,centena,decena,unidad;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISA = 0xFF;
    ANSELA = 0xFF;
    TRISB = 0xFF;
    ANSELB = 0xEE;
    WPUBbits.WPUB4 = 1;
    INTCON0bits.GIE = 1;    //interruptor global de inerrupciones habilitado
    INTCON0bits.INT0EDG = 0;//flanco negativo para INT0
    PIE1bits.INT0IE = 1;    //interrupcion externa INT0 habilitado
    INT0PPS = 0x0C;     //asignacion de RB4 para INT0
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISE = 0xFC;
    ANSELE = 0xFC;
    ADCON0bits.FM = 1; //right justify
    ADCON0bits.CS = 1; //ADCRC Clock
    ADCON0bits.ADON = 1;      //ADC On
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    U1BRGH = 00;
    U1BRGL = 25;      //BRG=25 para 9600 baudios con BRGS=0
    U1CON0 = 0x30;      //BRGS=0, TXEN=1, RXEN=0, MODE=00 (8bit async uart)
    RF0PPS = 0x20;       //asignación de RF0 para TX de UART1 
    U1CON2 = 0x00;
    U1CON1 = 0x80;      // UART1 enabled
    LCD_INIT();
}

unsigned int ADC_GetValue(unsigned char canal){
    ADPCH = canal; //RA0 is Analog channel
    ADCON0bits.GO = 1; //Start conversion
    while (ADCON0bits.GO); //Wait for conversion done
    return ((ADRESH << 8) + ADRESL);
}

void convierte(unsigned int numero){
    diezmillar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
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
        UART1_Data_Send(cadena[i]);
	}
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Semana 12");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Taller de Micro");
    UART1_String_Send("Semana 12");
    UART1_NewLine();
    UART1_String_Send("Taller de Micro");
//    __delay_ms(3000);
    BORRAR_LCD();
    UART1_NewLine();    
}


void main(void) {
    configuro();
    pantallazo();
    while(1){
        convierte(ADC_GetValue(0));
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("AN-0:");
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        convierte(ADC_GetValue(1));
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("AN-1:");
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
//        __delay_ms(500);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    convierte(ADC_GetValue(0));    
    UART1_String_Send("Canal AN-0:");
    UART1_Data_Send(millar+0x30);
    UART1_Data_Send(centena+0x30);
    UART1_Data_Send(decena+0x30);
    UART1_Data_Send(unidad+0x30);
    UART1_NewLine();
    convierte(ADC_GetValue(1));
    UART1_String_Send("Canal AN-1:");
    UART1_Data_Send(millar+0x30);
    UART1_Data_Send(centena+0x30);
    UART1_Data_Send(decena+0x30);
    UART1_Data_Send(unidad+0x30);
    UART1_NewLine();        
}
