#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define XTAL_FREQ 4000000UL

unsigned char diezmillar, millar, centena, decena, unidad;
unsigned int resultado_ADC;

void configuro(void){
    //configuracion de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 0;
    TRISCbits.TRISC6 = 0;
    ANSELCbits.ANSELC6 = 0;
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSELC7 = 0;
    TRISD = 0x00;
    ANSELD = 0x00;
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la izquierda
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On
    //configuracion inicial del LCD
    LCD_INIT();
}

void convierte(unsigned int numero){
    diezmillar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    resultado_ADC = (ADRESH << 8) + ADRESL;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Primer ejemplo");
    while(1){
        tomamuestra_ADC();
        convierte(resultado_ADC);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("ADC:");
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
