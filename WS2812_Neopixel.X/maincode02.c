/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 29 de septiembre de 2024, 09:23 PM
 */

#include <xc.h>
#include "cabecera.h"

#define _XTAL_FREQ 32000000UL

void configuro(void){
    //clock source config
    OSCCON1 = 0x60;     //NOSC=HFINTOSC, NDIV=1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
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
    //port config
    TRISFbits.TRISF3 = 0;   //onboard LED config
    ANSELFbits.ANSELF3 = 0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    RF0PPS = 0x01;      //CLC1out connected to RF0
}

void neopixel(unsigned char r, unsigned char g, unsigned char b){
    SPI1TXB = g;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = r;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = b;
    while(!SPI1STATUSbits.TXBE);
}

void main(void) {
    configuro();
    neopixel(0,0,0);
    __delay_ms(1);
    while(1){
        neopixel(127,0,0);
        __delay_ms(500);
        neopixel(0,127,0);
        __delay_ms(500);
        neopixel(0,0,127);
        __delay_ms(500);
        neopixel(127,127,0);
        __delay_ms(500);
        neopixel(0,127,127);
        __delay_ms(500);
        neopixel(127,127,127);
        __delay_ms(500);
    }
}

