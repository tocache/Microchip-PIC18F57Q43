#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int posicion = 0; //posicion aloja valores de 700 a 2300
unsigned int lectura_adc = 0;
float temporal = 0;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC divider 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;       //RB4 entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 digital (boton integrado)
    WPUBbits.WPUB4 = 1;         //RB4 pullup enabled
    TRISCbits.TRISC0 = 0;       //RC0 salida
    ANSELCbits.ANSELC0 = 0;     //RC0 digital (salida al servo)
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogico    
    //configuracion del Timer0
    T0CON0 = 0x90;
    T0CON1 = 0x43;
    PIR3bits.TMR0IF = 0;
    //configuracion de las interrupciones para el Timer0
    PIE3bits.TMR0IE = 1;        //habilitador de las ints del Timer0
    INTCON0bits.GIE = 1;        //habilitador global de interrupciones
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On    
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servito UPCino",14);
    while(1){
        tomamuestra_ADC();
        //ADRESH:ADRESL
        lectura_adc = (ADRESH << 8) + ADRESL;
        temporal = (lectura_adc / 2.56) + 700;
        posicion = temporal;
    }
}

void __interrupt(irq(IRQ_TMR0)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0;
    if(PORTCbits.RC0 == 1){
        LATCbits.LATC0 = 0;
        TMR0H = (((65535 - (20000- ((65535 - ((65535-posicion)+1))+1)))+1) >> 8) & 0x00FF;
        TMR0L = ((65535 - (20000- ((65535 - ((65535-posicion)+1))+1)))+1) & 0x00FF;
    }
    else{
        LATCbits.LATC0 = 1;
        TMR0H = (((65535-posicion)+1) >> 8) & 0x00FF;  //TON
        TMR0L = ((65535-posicion)+1) & 0x00FF;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
        
}