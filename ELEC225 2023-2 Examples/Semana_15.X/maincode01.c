#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;              //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //Inicializacion del I2C LCD
    I2C_LCD_INIT();
    //Configuracion de E/S para los HCSR04
    TRISE = 0xF8;       //RE0, RE1, RE2 como salidas
    ANSELE = 0xF8;      //RE0, RE1, RE2 como digitales
    TRISCbits.TRISC0 = 1;   //RC0 como entrada
    TRISCbits.TRISC1 = 1;   //RC1 como entrada
    TRISCbits.TRISC2 = 1;   //RC2 como entrada
    ANSELCbits.ANSELC0 = 0;   //RC0 como digital
    ANSELCbits.ANSELC1 = 0;   //RC1 como digital
    ANSELCbits.ANSELC2 = 0;   //RC2 como digital
    T1CLK = 0x01;       //Timer1 con fuente de reloj FOSC/4
    T1CON = 0x32;       //presc 1:8, rd16=1, async, timer1 OFF = 1us x cta   
}

unsigned int Read_HCSR04(unsigned char numero){
    //unsigned int cuentas;
    TMR1H = 0;
    TMR1L = 0;
    switch (numero){
        case 0:
            LATEbits.LATE0 = 1;
            __delay_us(10);
            LATEbits.LATE0 = 0;
            while(PORTCbits.RC0 == 0);
            T1CONbits.ON = 1;
            while(PORTCbits.RC0 == 1);
            T1CONbits.ON = 0;
            break;
        case 1:
            LATEbits.LATE1 = 1;
            __delay_us(10);
            LATEbits.LATE1 = 0;
            while(PORTCbits.RC1 == 0);
            T1CONbits.ON = 1;
            while(PORTCbits.RC1 == 1);
            T1CONbits.ON = 0;
            break;
        case 2:
            LATEbits.LATE2 = 1;
            __delay_us(10);
            LATEbits.LATE2 = 0;
            while(PORTCbits.RC2 == 0);
            T1CONbits.ON = 1;
            while(PORTCbits.RC2 == 1);
            T1CONbits.ON = 0;
            break;            
    }
    //cuentas = TMR1;
    return TMR1;
}

unsigned int calculo(unsigned int valor){
    float tiempo;
    unsigned int distancia;
    tiempo= (float)valor;
    tiempo= tiempo / 5.8;
    distancia = (int)tiempo + 1;
    return distancia;
}

void main(void) {
    configuro();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola mundo I2C");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
    while(1){
        I2C_POS_CURSOR(3,0);
        I2C_ESCRIBE_MENSAJE2("HCSR04-0:");
        I2C_LCD_ESCRIBE_VAR_INT(calculo(Read_HCSR04(0)),3,1);
        I2C_ESCRIBE_MENSAJE2("cm");
        __delay_ms(100);
        I2C_POS_CURSOR(4,0);
        I2C_ESCRIBE_MENSAJE2("HCSR04-1:");
        I2C_LCD_ESCRIBE_VAR_INT(calculo(Read_HCSR04(1)),3,1);
        I2C_ESCRIBE_MENSAJE2("cm");
        __delay_ms(100);
    }
}
