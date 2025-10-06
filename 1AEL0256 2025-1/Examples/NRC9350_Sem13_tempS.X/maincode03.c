#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_WS2812.h"
#define _XTAL_FREQ 32000000UL

volatile unsigned char cuenta = 0;
volatile unsigned int dht_temp, dht_humid;
volatile unsigned char estado = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //conf del neopixel
    RF2PPS = 0x01;
    TRISFbits.TRISF2 = 0;
    ANSELFbits.ANSELF2 = 0;
    //conf la INT0 e INT1
    INT0PPS = 0x08;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    INT1PPS = 0x09;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB1 = 1;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    PIE6bits.INT1IE = 1;
    PIR6bits.INT1IF = 0;
    INTCON0bits.INT0EDG = 0;
    INTCON0bits.INT1EDG = 0;
    INTCON0bits.GIE = 1;
}

void ws2812_update(void){
    switch(estado){
        case 0:
            WS2812_DATA_SEND(50,50,50);
            break;
        case 1:
            WS2812_DATA_SEND(50,50,0);
            break;
        case 2:
            WS2812_DATA_SEND(0,50,0);
            break;
        case 3:
            WS2812_DATA_SEND(50,0,0);
            break;
        case 4:
            WS2812_DATA_SEND(0,0,50);
            break;
    }
}

void main(void) {
    configuro();
    WS2812_INIT();      //inicializacion del neopixel
    I2C_LCD_INIT();
    I2C_POS_CURSOR(1,1);
    I2C_ESCRIBE_MENSAJE2("Hello UPCino!");
    I2C_POS_CURSOR(2,1);
    I2C_ESCRIBE_MENSAJE2("Elec Meca Bio");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("Temp DHT:");
        dht_temp = DHT_GetTemp(DHT22);
        I2C_LCD_ESCRIBE_VAR_INT(dht_temp/10, 2, 0);
        I2C_LCD_CHAR_GRADO();
        I2C_ENVIA_LCD_DATA('C');
        __delay_ms(1000);
        I2C_POS_CURSOR(2,0);
        I2C_ESCRIBE_MENSAJE2("Humid DHT:");
        dht_humid = DHT_GetHumid(DHT22);
        I2C_LCD_ESCRIBE_VAR_INT(dht_humid/10, 2, 0);
        I2C_ESCRIBE_MENSAJE2("%RH");
        __delay_ms(1000); 
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(estado == 4){
        estado = 0;
    }
    else{
        estado++;
    }
    ws2812_update();
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(estado == 0){
        estado = 4;
    }
    else{
        estado--;
    }
    ws2812_update();
}