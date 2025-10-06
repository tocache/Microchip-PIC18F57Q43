#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

//declaracion de variables globales
unsigned char lectura_ch0;
unsigned int tmr1_count;
float temporal;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    //Conf para leer el potenciometro en RA0
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    ADCON0bits.ADFM = 0;
    ADPCH = 0x00;
    ADREF = 0x00;
    ADCON0bits.ADON = 1;
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    TRISCbits.TRISC1 = 1;
    ANSELCbits.ANSELC1 = 0;
    T1CLK = 0x01;
    T1CON = 0x32;
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Sem14 UPC Micro");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ing. BioMecaEle");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

unsigned int HCSR04_Distance(void){
    unsigned int distancia;
    TMR1H = 0;
    TMR1L = 0;
    LATEbits.LATE0 = 1;
    __delay_us(10);
    LATEbits.LATE0 = 0;
    while(PORTCbits.RC1 == 0);
    T1CONbits.TMR1ON = 1;
    while(PORTCbits.RC1 == 1);
    T1CONbits.TMR1ON = 0;
    //las cuentas estan almacenadas en TMR1H:TMR1L
    tmr1_count = TMR1;
    temporal = tmr1_count/58.31;
    distancia = temporal;
    return distancia;
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        lectura_ch0 = ADRESH;
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC_CH0:");
        I2C_LCD_ESCRIBE_VAR_CHAR(lectura_ch0,3);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Dist:");
        I2C_LCD_ESCRIBE_VAR_INT(HCSR04_Distance(), 3, 0);
        I2C_ESCRIBE_MENSAJE2("cm");
    }
}
