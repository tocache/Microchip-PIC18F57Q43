#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

unsigned char duty_cycle = 0;
unsigned char centena, decena, unidad;
float temporal;

void configuro(void){
    //configuracion para oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x05;  //HFINTOSC a 5MHz
    OSCEN = 0x40;
    RF1PPS = 0x15;  //RF1 asignado a CCP1
    //configuracion para PWM
    TRISFbits.TRISF1 = 0;   //RF1 salida
    ANSELFbits.ANSELF1 = 0; //RF1 digital
    T2PR = 250;             //Periodo de PWM (f=4KHz)
    CCP1CON = 0x9C;         //CCP1 enabled, PWM, left justified
    CCPR1H = 125;           //duty cycle al 50%
    CCPR1L = 0;
    T2CON = 0xA0;           //TMR2 on, 1:4 presc
    T2CLKCON = 0x01;         //TMR2 con FOSC/4
    //configuracion para pulsador en RB4
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    INT0PPS = 0x0C;         //RB4 sera la INT0
    INTCON0bits.INT0EDG = 0;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    INTCON0bits.GIE = 1;
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}
void main(void) {
    configuro();
    LCD_INIT();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("PWM Generator");
    while(1){
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("f=4KHz DC=");
        convierte(duty_cycle);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR('%');
        temporal = duty_cycle * 2.5;
        CCPR1H = temporal;
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(duty_cycle == 100){
        duty_cycle = 0;
    }
    else{
        duty_cycle = duty_cycle + 5;
    }
}
