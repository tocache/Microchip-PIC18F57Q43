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
    //conf el hcsr04
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    TRISCbits.TRISC1 = 1;
    ANSELCbits.ANSELC1 = 0;
    //conf Timer5
    T5CLK = 0x01;
    T5CON = 0x32;
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

unsigned int lectura_HCSR04(void){
    float temporal;
    unsigned cuenta;
    LATEbits.LATE0 = 1;
    __delay_us(10);
    LATEbits.LATE0 = 0;
    TMR5 = 0;
    while(PORTCbits.RC1 == 0);
    T5CONbits.ON = 1;
    while(PORTCbits.RC1 == 1);
    T5CONbits.ON = 0;
    temporal = TMR5 / 58.31;
    cuenta = temporal;
    return cuenta;
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Dist: ");
        I2C_LCD_ESCRIBE_VAR_INT(lectura_HCSR04(),3,0);
        I2C_ESCRIBE_MENSAJE2("cm");        
        __delay_ms(50);
    }
}
