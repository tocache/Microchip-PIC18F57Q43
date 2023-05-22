#include <xc.h>
#include <pic18f57q43.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char centena, decena, unidad;

void configuro(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogico
    TRISCbits.TRISC2 = 0;       //RC2 como salida
    ANSELCbits.ANSELC2 = 0;     //RC2 como digital
    //configuracion del ADC
    ADCON0bits.ADFM = 0;    //justificacion a la izquierda
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On
    ADCON2 = 0x62;          //CRS=6, AVG mode
    ADRPT = 64;              //repeticiones para cumple 2^CRS
    //configuracion del CCP para PWM
    T2PR = 62;               //frecuencia de PWM a 1KHz
    RC2PPS = 0x15;          //PPS asignación de RC2 hacia CCP1
    CCP1CON = 0x9C;         //CCP1 ON, justificacion izquierda, PWM mode
    CCPR1H = 31;
    CCPR1L = 0;             //duty cycle a 50%
    T2CLKCON = 0x01;        //Timer2 Fosc/4
    T2CON = 0xC0;           //Timer2 ON psc 1:16
}

void lcd_config(void){
    __delay_ms(15);
    LCD_CONFIG();
    __delay_ms(15);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    //LATCbits.LATC2 = 1;
}

void splash_screen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo!");
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
}

void main(void) {
    configuro();
    lcd_config();
    splash_screen();
    while(1){
        tomamuestra_ADC();
        CCPR1L = ADRESH;
        convierte(ADRESH);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("ADC:");        
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ESCRIBE_MENSAJE2(" PREV:");        
        convierte(ADPREVH);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
