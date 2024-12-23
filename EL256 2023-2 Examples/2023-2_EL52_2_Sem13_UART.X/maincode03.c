#include <xc.h>
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
    U1CON0 = 0x30;
    U1CON1 = 0x80;
    U1CON2 = 0x00;
    RF0PPS = 0x20;           //RF0 esta conectado a UART1TX
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

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("EL52-2 Semana 13");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2(" uC PIC18F57Q43");
    U1_BYTE_SEND('H');
    U1_BYTE_SEND('o');
    U1_BYTE_SEND('l');
    U1_BYTE_SEND('a');    
    __delay_ms(3000);
    BORRAR_LCD();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("  Lectura ADC");
    U1_BYTE_SEND('M');
    U1_BYTE_SEND('u');
    U1_BYTE_SEND('n');
    U1_BYTE_SEND('d');
    U1_BYTE_SEND('o');
    
    while(1){
        POS_CURSOR(2,4);        
        LCD_ESCRIBE_VAR_INT(tomamuestra_ADC(0x00),4);
        __delay_ms(25);
    }
}
