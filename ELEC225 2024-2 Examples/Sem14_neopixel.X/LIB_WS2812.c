#include <xc.h>
#include "LIB_WS2812.h"

void WS2812_INIT(void){
    //Timer2 config
    T2CON = 0x80;       //TMR2=ON, PRESC=1:1, POSTS=1:1
    T2CLKCON = 0x01;    //TMR2 SOURCE = FOSC/4
    T2PR = 5;           //Limit value
    //SPI config
    SPI1CON0 = 0x83;    //SPI enabled, Master, BMODE=1
    SPI1CON1 = 0x40;    //default values
    SPI1CON2 = 0x02;    //TXR=1, RXR=0
    SPI1CLK = 0x06;     //CLK=TMR2_Posts
    //PWM config (CCP1)
    CCP1CON = 0x8C;     //CCP1 enabled, right aligned, PWM operation
    CCPR1H = 0x00;
    CCPR1L = 0x0A;      //Duty Cycle at 50%
    //CLC1 config
    CLCSELECT = 0x00;
    CLCnSEL0 = 0x1F;    //CLC1SEL0=CCP1 (PWM)
    CLCnSEL1 = 0x41;    //CLC1SEL1=SPI1_SCK
    CLCnSEL2 = 0x40;    //CLC1SEL2=SPI1_SDO
    CLCnGLS0 = 0x05;    //CLC1 Gate1 => INV_SEL0 INV_SEL1
    CLCnGLS1 = 0x10;    //CLC1 Gate2 => INV_SEL2
    CLCnGLS2 = 0x08;    //CLC1`Gate3 => SEL1
    CLCnGLS3 = 0x20;    //CLC1 Gate4 => SEL2
    CLCnPOL = 0x01;     //CLC1 Gate1 POL inverted
    CLCnCON = 0x80;     //CLC1 enabled, AND-OR mode    
};

void WS2812_DATA_SEND(unsigned char green, unsigned char red, unsigned char blue){
    SPI1TXB = green;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = red;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = blue;
    while(!SPI1STATUSbits.TXBE);    
};
