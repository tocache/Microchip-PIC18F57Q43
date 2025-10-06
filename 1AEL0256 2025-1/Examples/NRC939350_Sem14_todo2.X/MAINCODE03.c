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
    U1_INIT(BAUD_9600);
    //conf del ADC para RA0/ANA0
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.ADCS = 1;
    ADCON0bits.ADFM = 0;
    ADPCH = 0x00;       //RA0/ANA0 seleccionado
    ADREF = 0x00;       //Vref+=5V Vref-=0V
    ADCON0bits.ADON = 1;
    //conf el servo
    TRISFbits.TRISF5 = 0;
    ANSELFbits.ANSELF5 = 0;
}

void splash_screen(void){
    unsigned char x_var;
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2(" NRC9350 Micro ");  
    U1_STRING_SEND("NRC9350 Microcontroladores");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Loading");
    U1_NEWLINE();
    U1_STRING_SEND("Loading");
    for(x_var=0;x_var<7;x_var++){
        I2C_ENVIA_LCD_DATA('.');
        U1_BYTE_SEND('.');
        __delay_ms(300);
    }
    I2C_ESCRIBE_MENSAJE2("ok");
    U1_STRING_SEND("ok!");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
    U1_NEWLINE();
}

unsigned char adc_res;

void main(void) {
    configuro();
    splash_screen();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        adc_res = ADRESH;
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC CH0:");
        I2C_LCD_ESCRIBE_VAR_CHAR(adc_res,3);
        U1_STRING_SEND("ADC CH0:");
        U1_VAR_CHAR(adc_res,3);
        U1_BYTE_SEND(0x0D);
        switch(adc_res){
            case 0 ... 120:
                LATFbits.LATF5 = 1;
                __delay_us(500);
                LATFbits.LATF5 = 0;
                __delay_us(19500);
                break;
            case 121 ... 130:
                LATFbits.LATF5 = 1;
                __delay_us(1500);
                LATFbits.LATF5 = 0;
                __delay_us(18500);
                break;
            case 131 ... 255:
                LATFbits.LATF5 = 1;
                __delay_us(2500);
                LATFbits.LATF5 = 0;
                __delay_us(17500);
                break;
        }
        __delay_ms(50);
    }
}

