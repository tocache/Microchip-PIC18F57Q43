#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#include "U1SERIAL.h"
#define _XTAL_FREQ 32000000UL

unsigned char variable1 = 234;
unsigned int variable2 = 14582;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;         //HFINTOSC seleccionado y div 1:1
    OSCFRQ = 0x06;          //HFINTOSC a 32MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogico
    TRISBbits.TRISB0 = 1;       //RB0 como entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 como digital
    WPUBbits.WPUB0 = 1;         //RB0 pullup enabled
    TRISBbits.TRISB1 = 1;       //RB1 como entrada
    ANSELBbits.ANSELB1 = 0;     //RB1 como digital
    WPUBbits.WPUB1 = 1;         //RB1 pullup enabled
    TRISCbits.TRISC0 = 0;       //RC0 como salida
    ANSELCbits.ANSELC0 = 0;     //RC0 como digital
    TRISCbits.TRISC1 = 1;       //RC1 como salida
    ANSELCbits.ANSELC1 = 0;     //RC1 como digital
    TRISFbits.TRISF0 = 0;       //RF0 como salida (U1 TX)
    ANSELFbits.ANSELF0 = 0;     //RF0 como digital
    TRISFbits.TRISF1 = 1;       //RF1 como entrada (U1 RX)
    ANSELFbits.ANSELF1 = 0;     //RF1 como digital
    //configuracion de interrupciones para los botones
    PIE1bits.INT0IE = 1;            //INT0 habilitado
    PIR1bits.INT0IF = 0;            //INT0 bandera abajo
    INTCON0bits.INT0EDG = 0;        //INT0 en flanco negativo
    PIE6bits.INT1IE = 1;            //INT1 habilitado
    PIR6bits.INT1IF = 0;            //INT1 bandera abajo
    INTCON0bits.INT1EDG = 0;        //INT1 en flanco negativo
    INTCON0bits.GIE = 1;            //habilitador global activado
    //inicializacion del LCD
    LCD_INIT();
    //inicializacion del UART 1
    U1_INIT(BAUD19200);
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Micro Semana 13");
    while(1){
        U1_STRING_SEND("Hola");
        U1_NEWLINE();
        U1_STRING_SEND("Variable1: ");
        U1_ESCRIBE_VAR_CHAR(variable1, 3);
        U1_NEWLINE();
        U1_STRING_SEND("Variable2: ");
        U1_ESCRIBE_VAR_INT(variable2, 5);
        U1_NEWLINE();
        __delay_ms(3000);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    U1_STRING_SEND("Se pulso boton en INT0");
    U1_NEWLINE();
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    U1_STRING_SEND("Se pulso boton en INT1");
    U1_NEWLINE();
}

