#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_WS2812.h"
#define _XTAL_FREQ 32000000UL


void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //config los pulsadores
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB1 = 1;
    //config las INTs
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    PIE6bits.INT1IE = 1;
    PIR6bits.INT1IF = 0;
    INTCON0bits.INT0EDG = 0;
    INTCON0bits.INT1EDG = 0;
    INT0PPS = 0x08;
    INT1PPS = 0x09;
    INTCON0bits.GIE = 1;
    //inicializacion de libs
    WS2812_INIT();
    I2C_LCD_INIT();
}

void main(void) {
    configuro();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Semana 13 UPC");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Quiero minilab");
    __delay_ms(3000);
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp DHT11:");
        I2C_LCD_ESCRIBE_VAR_CHAR(DHT_GetTemp(DHT11), 2);
        I2C_LCD_CHAR_GRADO();
        I2C_ENVIA_LCD_DATA('C');
        __delay_ms(1000);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humed DHT11:");
        I2C_LCD_ESCRIBE_VAR_CHAR(DHT_GetHumid(DHT11), 2);
        I2C_ESCRIBE_MENSAJE2("%RH");
        __delay_ms(1000);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
}
