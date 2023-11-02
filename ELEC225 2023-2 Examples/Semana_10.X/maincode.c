#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC, posts 1:1
    OSCFRQ = 0x05;      //HFINTOSC a 16MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion del LCD
    LCD_INIT();
    //configuracion del ADC
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogica
    ADCON0bits.ADFM = 1;        //just derecha
    ADCON0bits.CS = 1;          //clock source ADCRC
    ADPCH = 0x00;               //ANA0 selected
    ADCON0bits.ON = 1;          //ADC on
    //configuracion para PWM
    RF1PPS = 0x15;  //RF1 asignado a CCP1    
    TRISFbits.TRISF1 = 0;   //RF1 salida
    ANSELFbits.ANSELF1 = 0; //RF1 digital
    T2PR = 250;             //Periodo de PWM (f=4KHz)
    CCP1CON = 0x9C;         //CCP1 enabled, PWM, left justified
    CCPR1H = 125;           //duty cycle al 50%
    CCPR1L = 0;
    T2CON = 0xA0;           //TMR2 on, 1:4 presc
    T2CLKCON = 0x01;         //TMR2 con FOSC/4    
}

unsigned int tomamuestra_ADC(unsigned char canal){
    unsigned int lectura = 0;
    float temporal;
    ADPCH = canal;
    ADCON0bits.GO = 1;          //inicio una toma de muestra
    while(ADCON0bits.GO == 1);  //esperar a que termine de convertir
    lectura = (ADRESH << 8) + ADRESL;
    temporal = lectura * 0.061;
    CCPR1H = temporal;
    return lectura;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Los Santos");
    while(1){
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("ADC CH0:");
        LCD_ESCRIBE_VAR_INT(tomamuestra_ADC(0), 4);
    }
}
