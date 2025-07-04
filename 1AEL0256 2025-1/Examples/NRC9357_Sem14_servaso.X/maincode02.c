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
}

void splash_screen(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2(" Micro NRC9357  ");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("UPC 2025-1 Sem14");
    __delay_ms(2000);
    I2C_BORRAR_LCD();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Loading system  ");
    I2C_POS_CURSOR(2,0);
    unsigned char itera;
    for(itera=0;itera<14;itera++){
        I2C_ENVIA_LCD_DATA('*');
        __delay_ms(500);
    }
    __delay_ms(500);
    I2C_ESCRIBE_MENSAJE2("ok");    
    __delay_ms(2000);
    I2C_BORRAR_LCD();
}

unsigned char lectura_ADC_RA0(void){
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE == 1);
    return ADRESH;
}

void main(void) {
    configuro();
    splash_screen();
    while(1){
        unsigned char lectura;
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC_CH0:");
        lectura = lectura_ADC_RA0();
        I2C_LCD_ESCRIBE_VAR_CHAR(lectura,3);
        switch(lectura){
            case 0 ... 80:
                LATFbits.LATF5 = 1;
                __delay_us(500);
                LATFbits.LATF5 = 0;
                __delay_us(19500);
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Servo 000");
                I2C_LCD_CHAR_GRADO();
                break;
            case 81 ... 160:
                LATFbits.LATF5 = 1;
                __delay_us(1500);
                LATFbits.LATF5 = 0;
                __delay_us(18500);
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Servo 090");
                I2C_LCD_CHAR_GRADO();
                
                break;
            case 161 ... 255:
                LATFbits.LATF5 = 1;
                __delay_us(2500);
                LATFbits.LATF5 = 0;
                __delay_us(17500);
                break;
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Servo 180");
                I2C_LCD_CHAR_GRADO();
        }
        __delay_ms(50);
    }
}
