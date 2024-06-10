#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

unsigned char pantalla = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;          //HFINTOSC a 16MHz
    OSCEN = 0x40;
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    LATCbits.LATC0 = 1;     //para encender el backlight del LCD
    //configuracion del ADC
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;    //ADC On
    //configuracion de INTs
    TRISB = 0xFF;           //RB0, RB1 y RB2 como entradas
    ANSELB = 0xF0;          //RB0, RB1 y RB2 como digitales
    WPUB = 0x07;            //RB0, RB1 y RB2 weakpullup activados
    INTCON0bits.INT0EDG = 0;    //INT0 flanco descendente
    INTCON0bits.INT1EDG = 0;    //INT1 flanco descendente
    INTCON0bits.INT2EDG = 0;    //INT2 flanco descendente
    PIE1bits.INT0IE = 1;        //INT0 habilitado
    PIE6bits.INT1IE = 1;        //INT1 habilitado
    PIE10bits.INT2IE = 1;       //INT2 habilitado
    INTCON0bits.GIE = 1;        //Global interrupt habilitado
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
        switch(pantalla){
            case 0:
                ESCRIBE_MENSAJE2("A/D Ch0:");
                LCD_ESCRIBE_VAR_INT(tomamuestra_ADC(),4);
                ENVIA_CHAR(' ');                                
                ENVIA_CHAR(' ');                                
                break;
            case 1:
                ESCRIBE_MENSAJE2("Pot value:");
                LCD_ESCRIBE_VAR_INT((tomamuestra_ADC()/410),2);
                ENVIA_CHAR('K');                
                ENVIA_CHAR(0xF4);
                ENVIA_CHAR(' ');                                
                ENVIA_CHAR(' ');                                
                break;
            case 2:
                ESCRIBE_MENSAJE2("Voltage:  ");
                LCD_ESCRIBE_VAR_INT((tomamuestra_ADC()/820),1);
                ENVIA_CHAR('V');                
                ENVIA_CHAR(' ');                                
                ENVIA_CHAR(' ');                                
                break;
        }
    }
}
//zona de atencion a las interrupciones
void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    pantalla = 0;
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    pantalla = 1;
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    pantalla = 2;
}

void __interrupt(irq(default)) default_ISR(void){
}