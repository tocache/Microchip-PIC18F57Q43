#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;          //HFINTOSC a 16MHz
    OSCEN = 0x40;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    LATCbits.LATC0 = 1;     //para encender el backlight del LCD
    TRISBbits.TRISB3 = 0;
    ANSELBbits.ANSELB3 = 0;
    LATBbits.LATB3 = 1;     //para encender el backlight del LCD
    
    //configuracion del ADC
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;    //ADC On       
}

unsigned int tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return ((ADRESH << 8) + ADRESL);
}

void main(void) {
    configuro();
    LCD_INIT();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("HOLA MUNDO!");
    while(1){
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("A/D Ch0:");
        LCD_ESCRIBE_VAR_INT(tomamuestra_ADC(),4);
        __delay_ms(10);
    }
}
