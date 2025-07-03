#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#include "LIB_DHT.h"
#include "LIB_WS2812.h"
#define _XTAL_FREQ 32000000UL

unsigned char estado_color = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    WS2812_INIT();
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
}

void main(void) {
    configuro();
    while(1){
        switch(estado_color){
            case 0:
                WS2812_DATA_SEND(255, 0, 0);
                break;
            case 1:
                WS2812_DATA_SEND(0, 255, 0);
                break;
            case 2:
                WS2812_DATA_SEND(0, 0, 255);
                break;
            case 3:
                WS2812_DATA_SEND(255, 255, 0);
                break;
            case 4:
                WS2812_DATA_SEND(0, 255, 255);
                break;
            case 5:
                WS2812_DATA_SEND(255, 0, 255);
                break;
            case 6:
                WS2812_DATA_SEND(255, 255, 255);
                break;
        }
        __delay_ms(50);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(estado_color == 6){
        estado_color = 0;
    }
    else{
        estado_color++;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(estado_color == 0){
        estado_color = 6;
    }
    else{
        estado_color--;
    }
}
