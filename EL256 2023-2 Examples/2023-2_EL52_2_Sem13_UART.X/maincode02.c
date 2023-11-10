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
    //configuracion del LCD
    LCD_INIT();
}

unsigned int tomamuestra_ADC(unsigned char canal){
    ADPCH = canal;           //canal analógico RA0
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH << 8) + ADRESL;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("EL52-2 Semana 13");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2(" uC PIC18F57Q43");
    __delay_ms(3000);
    BORRAR_LCD();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("  Lectura ADC");
    while(1){
        POS_CURSOR(2,4);        
        LCD_ESCRIBE_VAR_INT(tomamuestra_ADC(0x00),4);
        __delay_ms(25);
    }
}
