#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL
//#define backlight 0
//#define contrast 1

unsigned char nivel_backlight = 9;
unsigned char nivel_contraste = 0;
unsigned char ajuste = 1;

void configuro(void){
    //configuracion del reloj a 16M
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;
    OSCEN = 0x40;
    //configuracion de los puertos
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSELC1 = 0;
    TRISCbits.TRISC2 = 0;
    ANSELCbits.ANSELC2 = 0;
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB1 = 1;
    TRISBbits.TRISB2 = 1;
    ANSELBbits.ANSELB2 = 0;
    WPUBbits.WPUB2 = 1;
    //configuracion de las interrupciones
    //INTCON0bits.GIE = 1;
    PIE1bits.INT0IE = 1;
    PIE6bits.INT1IE = 1;
    PIE10bits.INT2IE = 1;
    INTCON0bits.INT0EDG = 0;
    INTCON0bits.INT1EDG = 0;
    INTCON0bits.INT2EDG = 0;
    INT0PPS = 0x0C;
    INT1PPS = 0x09;
    INT2PPS = 0x0A;
    //configuracion del CCP1 para que entregue PWM al contraste del LCD
    T2PR = 62;               //frecuencia de PWM a 1KHz
    RC2PPS = 0x15;          //PPS asignación de RC2 hacia CCP1
    CCP1CON = 0x9C;         //CCP1 ON, justificacion izquierda, PWM mode
    CCPR1H = 0;
    CCPR1L = 0;             //duty cycle a 50%
    T2CLKCON = 0x01;        //Timer2 Fosc/4
    T2CON = 0xC0;           //Timer2 ON psc 1:16
    //configuracion del CCP2 para que entregue PWM a la luz de fondo del LCD
    RC1PPS = 0x16;          //PPS asignacion de RC1 hacia CCP2
    CCP2CON = 0x9C;         //CCP2 ON, justificacion izquierda, PWM mode
    CCPR2H = 62;
    CCPR2L = 0;             //duty cycle a 50%
    //configuracion del LCD
    LCD_INIT();
    //configuraciones de prueba
    TRISFbits.TRISF3 = 0;
    ANSELFbits.ANSELF3 = 0;
}


void main(void) {
    configuro();
    while(1){
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("Laboratorio 3");
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("Retiro masivo");
        LATFbits.LATF3 = 0;        
        __delay_ms(100);
        LATFbits.LATF3 = 1;        
        __delay_ms(100);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(ajuste == 0){
        ajuste = 1;
    }
    else{
        ajuste = 0;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(ajuste == 0){
        switch(nivel_backlight){
            case 0:
                CCPR2H = 0;
                nivel_backlight = 1;
                break;
            case 1:
                CCPR2H = 7;
                nivel_backlight = 2;
                break;
            case 2:
                CCPR2H = 14;
                nivel_backlight = 3;
                break;
            case 3:
                CCPR2H = 21;
                nivel_backlight = 4;
                break;
            case 4:
                CCPR2H = 28;
                nivel_backlight = 5;
                break;
            case 5:
                CCPR2H = 35;
                nivel_backlight = 6;
                break;
            case 6:
                CCPR2H = 42;
                nivel_backlight = 7;
                break;
            case 7:
                CCPR2H = 49;
                nivel_backlight = 8;
                break;
            case 8:
                CCPR2H = 56;
                nivel_backlight = 9;
                break;
            case 9:
                CCPR2H = 62;
                nivel_backlight = 0;
                break;
        }
    }
    else{
        switch(nivel_contraste){
            case 0:
                CCPR1H = 0;
                nivel_contraste = 1;
                break;
            case 1:
                CCPR1H = 7;
                nivel_contraste = 2;
                break;
            case 2:
                CCPR1H = 14;
                nivel_contraste = 3;
                break;
            case 3:
                CCPR1H = 21;
                nivel_contraste = 4;
                break;
            case 4:
                CCPR1H = 28;
                nivel_contraste = 5;
                break;
            case 5:
                CCPR1H = 35;
                nivel_contraste = 6;
                break;
            case 6:
                CCPR1H = 42;
                nivel_contraste = 7;
                break;
            case 7:
                CCPR1H = 49;
                nivel_contraste = 8;
                break;
            case 8:
                CCPR1H = 56;
                nivel_contraste = 9;
                break;
            case 9:
                CCPR1H = 62;
                nivel_contraste = 0;
                break;
        }
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    if(ajuste == 0){
        switch(nivel_backlight){
            case 0:
                CCPR2H = 0;
                nivel_backlight = 9;
                break;
            case 1:
                CCPR2H = 7;
                nivel_backlight = 0;
                break;
            case 2:
                CCPR2H = 14;
                nivel_backlight = 1;
                break;
            case 3:
                CCPR2H = 21;
                nivel_backlight = 2;
                break;
            case 4:
                CCPR2H = 28;
                nivel_backlight = 3;
                break;
            case 5:
                CCPR2H = 35;
                nivel_backlight = 4;
                break;
            case 6:
                CCPR2H = 42;
                nivel_backlight = 5;
                break;
            case 7:
                CCPR2H = 49;
                nivel_backlight = 6;
                break;
            case 8:
                CCPR2H = 56;
                nivel_backlight = 7;
                break;
            case 9:
                CCPR2H = 62;
                nivel_backlight = 8;
                break;
        }
    }
    else{
        switch(nivel_contraste){
            case 0:
                CCPR1H = 0;
                nivel_contraste = 9;
                break;
            case 1:
                CCPR1H = 7;
                nivel_contraste = 0;
                break;
            case 2:
                CCPR1H = 14;
                nivel_contraste = 1;
                break;
            case 3:
                CCPR1H = 21;
                nivel_contraste = 2;
                break;
            case 4:
                CCPR1H = 28;
                nivel_contraste = 3;
                break;
            case 5:
                CCPR1H = 35;
                nivel_contraste = 4;
                break;
            case 6:
                CCPR1H = 42;
                nivel_contraste = 5;
                break;
            case 7:
                CCPR1H = 49;
                nivel_contraste = 6;
                break;
            case 8:
                CCPR1H = 56;
                nivel_contraste = 7;
                break;
            case 9:
                CCPR1H = 62;
                nivel_contraste = 8;
                break;
        }
    }
}