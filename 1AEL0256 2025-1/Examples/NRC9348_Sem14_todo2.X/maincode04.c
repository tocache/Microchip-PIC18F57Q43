#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

//declaracion de variables globales
unsigned char lectura_ch0;
unsigned int tmr1_count;
unsigned int distancia_hcsr04;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    U1_INIT(BAUD_9600);
    //Conf para leer el potenciometro en RA0
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    ADCON0bits.ADFM = 0;
    ADPCH = 0x00;
    ADREF = 0x00;
    ADCON0bits.ADON = 1;
    //Conf para usar el HCSR04
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    TRISCbits.TRISC1 = 1;
    ANSELCbits.ANSELC1 = 0;
    T1CLK = 0x01;
    T1CON = 0x32;
    //Conf para usar el servomecanismo
    TRISFbits.TRISF5 = 0;
    ANSELFbits.ANSELF5 = 0;
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Sem14 UPC Micro");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ing. BioMecaEle");
    U1_STRING_SEND("Hola UPCino estoy mandando datos seriales a la PC!");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

unsigned int HCSR04_Distance(void){
    float temporal;
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
        distancia_hcsr04 = HCSR04_Distance();
        I2C_LCD_ESCRIBE_VAR_INT(distancia_hcsr04, 3, 0);
        I2C_ESCRIBE_MENSAJE2("cm");
        if(distancia_hcsr04 <= 6){
            LATFbits.LATF5 = 1;
            __delay_us(700);
            LATFbits.LATF5 = 0;
            __delay_us(19300);
        }
        else if(distancia_hcsr04 >= 12){
            LATFbits.LATF5 = 1;
            __delay_us(2300);
            LATFbits.LATF5 = 0;
            __delay_us(17700);
        }
    }
}
