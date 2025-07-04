#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    //conf adc para ra0
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.ADCS = 1;
    ADREF = 0x00;
    ADPCH = 0x00;
    ADCON0bits.ADFM = 0;
    ADCON0bits.ADON = 1;
    U1_INIT(BAUD_9600);
    //conf el servo
    TRISFbits.TRISF5 = 0;
    ANSELFbits.ANSELF5 = 0;
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Micro UPC Sem14 ");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ultimo lab :(   ");
    U1_STRING_SEND("************************************");
    U1_NEWLINE();
    U1_STRING_SEND("*                                  *");
    U1_NEWLINE();
    U1_STRING_SEND("* Microcontroladores UPC Semana 14 *");
    U1_NEWLINE();
    U1_STRING_SEND("* Sistema de acceso al Curiosity   *");
    U1_NEWLINE();
    U1_STRING_SEND("* Inicializando sistema operativo  *");
    U1_NEWLINE();
    U1_STRING_SEND("*                                  *");
    U1_NEWLINE();
    U1_STRING_SEND("************************************");
    U1_NEWLINE();
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

unsigned char lectura_ADC_RA0(void){
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE == 1);
    return ADRESH;
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        unsigned char lectura;
        lectura = lectura_ADC_RA0();
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC-0:");
        I2C_LCD_ESCRIBE_VAR_CHAR(lectura, 3);
        U1_STRING_SEND("ADC-0:");
        U1_VAR_CHAR(lectura, 3);
        U1_NEWLINE();
        switch(lectura){
            case 0 ... 60:
                LATFbits.LATF5 = 1;
                __delay_us(500);
                LATFbits.LATF5 = 0;
                __delay_us(19500);
                break;
            case 61 ... 120:
                LATFbits.LATF5 = 1;
                __delay_us(1500);
                LATFbits.LATF5 = 0;
                __delay_us(18500);
                break;
            case 121 ... 255:
                LATFbits.LATF5 = 1;
                __delay_us(2500);
                LATFbits.LATF5 = 0;
                __delay_us(17500);
                break;
        }
        __delay_ms(50);
    }
}
