#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion de fuente de reloj al CPU:
    OSCCON1 = 0x60;             //HFINTOSC
    OSCFRQ = 0x02;              //HFINTOSC a 4MHz
    OSCEN = 0x40;               //HFINTOSC habilitado
    //configuracion de E/S:
    TRISD = 0x00;               //RD salidas
    ANSELD = 0x00;              //RD digitales
    TRISAbits.TRISA0 = 1;       //RA0 entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 analogica
    TRISBbits.TRISB0 = 1;       //RB0 entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 digital
    WPUBbits.WPUB0 = 1;         //RB0 pullup activado
    TRISCbits.TRISC2 = 0;       //RC2 salida
    ANSELCbits.ANSELC2 = 0;     //RC2 digital
    //configuracion de interrupciones
    INTCON0bits.GIE = 1;        //ints habilitadas
    INTCON0bits.INT0EDG = 0;    //flanco negativo para int0
    PIE1bits.INT0IE = 1;        //INT0 habilitada
}

void LCD_Init(void){
    __delay_ms(18);
    LCD_CONFIG();
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);    
}

void main(void) {
    configuro();
    LCD_Init();
    while(1){
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Hola Mundo",10);
    }
}

void __interrupt() INT0_ISR(){
    PIR1bits.INT0IF = 0;
    LATCbits.LATC2 = ~LATCbits.LATC2;
}