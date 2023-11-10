#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB1 = 1;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    TRISFbits.TRISF1 = 1;
    ANSELFbits.ANSELF1 = 0;
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On
    //configuracion del UART
    U1BRGH = 0;
    U1BRGL = 207;           //UART1 a 9600 baudios
    U1CON0 = 0x30;          //TX enabled, RX enabled
    U1CON1 = 0x80;
    U1CON2 = 0x00;
    RF0PPS = 0x20;           //RF0 esta conectado a UART1TX
    U1RXPPS = 0x29;             //RF1 esta conectado a UART1RX
    //configuracion de las interrupciones
    PIE4bits.U1RXIE = 1;
    PIR4bits.U1RXIF = 0;
    INTCON0bits.GIE = 1;
    //configuracion del LCD
    LCD_INIT();
}

unsigned int tomamuestra_ADC(unsigned char canal){
    ADPCH = canal;           //canal analógico RA0
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH << 8) + ADRESL;
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void U1_STRING_SEND(const char *cadena)
{
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
}

void U1_VAR_INT_SEND(unsigned int numero, unsigned char n_digitos){
    unsigned char d_millar, millar, centena, decena, unidad;  //variables de funcion convierte
    d_millar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 2:
            U1_BYTE_SEND(decena+0x30);
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 3:
            U1_BYTE_SEND(centena+0x30);
            U1_BYTE_SEND(decena+0x30);
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 4:
            U1_BYTE_SEND(millar+0x30);
            U1_BYTE_SEND(centena+0x30);
            U1_BYTE_SEND(decena+0x30);
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 5:
            U1_BYTE_SEND(d_millar+0x30);
            U1_BYTE_SEND(millar+0x30);
            U1_BYTE_SEND(centena+0x30);
            U1_BYTE_SEND(decena+0x30);
            U1_BYTE_SEND(unidad+0x30);
            break;
    }
}

void U1_NEWLINE(void){
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("EL52-2 Semana 13");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2(" uC PIC18F57Q43");
    U1_STRING_SEND("Hola");
    U1_NEWLINE();
    __delay_ms(3000);
    BORRAR_LCD();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("  Lectura ADC");
    U1_STRING_SEND("Mundo");
    U1_NEWLINE();
    while(1){
        POS_CURSOR(2,4);
        unsigned int lectura_adc;
        lectura_adc = tomamuestra_ADC(0x00);
        LCD_ESCRIBE_VAR_INT(lectura_adc,4);
        U1_STRING_SEND("Canal ANA0:");
        U1_VAR_INT_SEND(lectura_adc,4);
        U1_NEWLINE();
        __delay_ms(25);
    }
}

void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    switch(U1RXB){
        case '1':
            LATCbits.LATC0 = 1;
            break;
        case '2':
            LATCbits.LATC0 = 0;
            break;
        case '3':
            LATCbits.LATC1 = 1;
            break;
        case '4':
            LATCbits.LATC1 = 0;
            break;
    }
}
