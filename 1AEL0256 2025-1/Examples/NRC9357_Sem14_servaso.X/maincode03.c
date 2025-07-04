#include <xc.h>
#include "I2C_LCD.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf fuente reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //conf I2C_LCD
    I2C_LCD_INIT();
    //conf ADC
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.ADCS = 1;
    ADCON0bits.ADFM = 0;
    ADPCH = 0x00;
    ADREF = 0x00;
    ADCON0bits.ADON = 1;
    //conf servo
    TRISFbits.TRISF5 = 0;
    ANSELFbits.ANSELF5 = 0;
    //conf HCSR04
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    TRISCbits.TRISC1 = 1;
    ANSELCbits.ANSELC1 = 0;
    T3CLK = 0x01;
    T3CON = 0x32;
    //conf UART
    U1_INIT(BAUD_9600);
}

void splash_screen(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2(" Micro NRC9357  ");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("UPC 2025-1 Sem14");
    U1_STRING_SEND(" Micro NRC9357  ");
    U1_NEWLINE();
    U1_STRING_SEND("UPC 2025-1 Sem14");
    U1_NEWLINE();
    __delay_ms(2000);
    I2C_BORRAR_LCD();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Loading system  ");
    U1_STRING_SEND("Loading system  ");
    U1_NEWLINE();
    I2C_POS_CURSOR(2,0);
    unsigned char itera;
    for(itera=0;itera<14;itera++){
        I2C_ENVIA_LCD_DATA('*');
        U1_BYTE_SEND('*');
        __delay_ms(500);
    }
    __delay_ms(500);
    I2C_ESCRIBE_MENSAJE2("ok"); 
    U1_STRING_SEND("ok");
    __delay_ms(2000);
    I2C_BORRAR_LCD();
    U1_NEWLINE();
}

unsigned char lectura_ADC_RA0(void){
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE == 1);
    return ADRESH;
}

unsigned int lectura_HCSR04(void){
    float temporal;
    unsigned int distancia;
    LATEbits.LATE0 = 1;
    __delay_us(10);
    LATEbits.LATE0 = 0;
    TMR3 = 0;
    while(PORTCbits.RC1 == 0);
    T3CONbits.ON = 1;
    while(PORTCbits.RC1 == 1);
    T3CONbits.ON = 0;
    temporal = TMR3 / 58.31;
    distancia = temporal;
    return distancia;
}

void main(void) {
    configuro();
    splash_screen();
    while(1){
        unsigned char analog;
        unsigned int distancia;
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC_CH0:");
        analog = lectura_ADC_RA0();
        I2C_LCD_ESCRIBE_VAR_CHAR(analog,3);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Dist:");
        distancia = lectura_HCSR04();
        I2C_LCD_ESCRIBE_VAR_INT(distancia,3,0);
        I2C_ESCRIBE_MENSAJE2("cm");
        __delay_ms(50);
    }
}
