#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

unsigned char posicion = 0;     //0 es cero grados, 1 es 90 grados, 2 es 180 grados
unsigned char x = 2000;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC div 1:1
    OSCFRQ = 0x05;      //HFINTOSC a 16 MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISCbits.TRISC0 = 0;       //RC0 como salida
    ANSELCbits.ANSELC0 = 0;     //RC0 como digital
    TRISBbits.TRISB0 = 1;       //RB0 como entrada
    ANSELBbits.ANSELB0 = 0;     //RB0 como digital
    WPUBbits.WPUB0 = 1;          //RB0 pullup enabled
    TRISBbits.TRISB1 = 1;       //RB1 como entrada
    ANSELBbits.ANSELB1 = 0;     //RB1 como digital
    WPUBbits.WPUB1 = 1;          //RB1 pullup enabled
    TRISBbits.TRISB2 = 1;       //RB2 como entrada
    ANSELBbits.ANSELB2 = 0;     //RB2 como digital
    WPUBbits.WPUB2 = 1;          //RB2 pullup enabled
    //configuracion de las interrupciones
    PIE1bits.INT0IE = 1;        //INT0 habilitada
    PIR1bits.INT0IF = 0;        //bandera de INT0 abajo
    PIE6bits.INT1IE = 1;        //INT1 habilitada
    PIR6bits.INT1IF = 0;        //bandera de INT1 abajo
    PIE10bits.INT2IE = 1;       //INT2 habilitada
    PIR10bits.INT2IF = 0;       //bandera de INT2 abajo
    INTCON0bits.GIE = 1;        //habilitador global de interrupciones activado
    //configuracion del LCD
    LCD_INIT();                 //inicializacion del LCD
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Sesion 11 UPAO");
    while(1){
        switch(posicion){
            case 0:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Servo pos:000");
                LCD_CHAR_GRADO();           //impresion del caracter de grado en el display
                LATCbits.LATC0 = 1;     //RC0 a uno
                __delay_us(x);       //retardo de 2ms
                LATCbits.LATC0 = 0;     //RC0 a cero
                __delay_us(20000 - x);       //retardo de 18ms
                break;
            case 1:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Servo pos:090");
                LCD_CHAR_GRADO();           //impresion del caracter de grado en el display
                LATCbits.LATC0 = 1;     //RC0 a uno
                __delay_us(1500);       //retardo de 1.5ms
                LATCbits.LATC0 = 0;     //RC0 a cero
                __delay_us(18500);       //retardo de 18.5ms
                break;
            case 2:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Servo pos:180");
                LCD_CHAR_GRADO();           //impresion del caracter de grado en el display
                LATCbits.LATC0 = 1;     //RC0 a uno
                __delay_us(1000);       //retardo de 1ms
                LATCbits.LATC0 = 0;     //RC0 a cero
                __delay_us(19000);       //retardo de 19ms
                break;
        }
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;        //bajamos la bandera INT0IF
    posicion = 0;
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;        //bajamos la bandera INT1IF
    posicion = 1;
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;        //bajamos la bandera INT2IF
    posicion = 2;
}