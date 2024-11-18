/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 29 de septiembre de 2024, 09:23 PM
 */

#include <xc.h>
#include "cabecera.h"

#define _XTAL_FREQ 32000000UL

unsigned char led_uno[]={0,0,0,0,0,0,0,0,0,255};
unsigned char led_dos[]={0,0,0,0,0,0,0,0,255,0};
unsigned char led_tres[]={0,0,0,0,0,0,0,255,0,0};
unsigned char led_cuatro[]={0,0,0,0,0,0,255,0,0,0};
unsigned char led_cinco[]={0,0,0,0,0,255,0,0,0,0};
unsigned char led_seis[]={0,0,0,0,255,0,0,0,0,0};
unsigned char led_siete[]={0,0,0,255,0,0,0,0,0,0};
unsigned char led_ocho[]={0,0,255,0,0,0,0,0,0,0};
unsigned char led_nueve[]={0,255,0,0,0,0,0,0,0,0};
unsigned char led_diez[]={255,0,0,0,0,0,0,0,0,0};

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
    SPI1TXB = r;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = g;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = b;
    while(!SPI1STATUSbits.TXBE);
}

void tira_neopixel(unsigned char *led){
    neopixel(led[0],0,0);
    neopixel(led[1],0,0);
    neopixel(led[2],0,0);
    neopixel(led[3],0,0);
    neopixel(led[4],0,0);
    neopixel(led[5],0,0);
    neopixel(led[6],0,0);
    neopixel(led[7],0,0);
    neopixel(led[8],0,0);
    neopixel(led[9],0,0);
}

/*void tira_neopixel(unsigned char *led){
    neopixel(led[0],led[0],led[0]);
    neopixel(led[1],led[1],led[1]);
    neopixel(led[1],led[1],led[1]);
    neopixel(led[2],led[2],led[2]);
    neopixel(led[3],led[3],led[3]);
    neopixel(led[4],led[4],led[4]);
    neopixel(led[5],led[5],led[5]);
    neopixel(led[6],led[6],led[6]);
    neopixel(led[7],led[7],led[7]);
    neopixel(led[8],led[8],led[8]);
    neopixel(led[9],led[9],led[9]);
}*/

void tira_neopixel2(unsigned char *led){
    neopixel(0, led[0],0);
    neopixel(0, led[1],0);
    neopixel(0, led[2],0);
    neopixel(0, led[3],0);
    neopixel(0, led[4],0);
    neopixel(0, led[5],0);
    neopixel(0, led[6],0);
    neopixel(0, led[7],0);
    neopixel(0, led[8],0);
    neopixel(0, led[9],0);
}

void tira_neopixel3(unsigned char *led){
    neopixel(0,0,led[0]);
    neopixel(0,0,led[1]);
    neopixel(0,0,led[2]);
    neopixel(0,0,led[3]);
    neopixel(0,0,led[4]);
    neopixel(0,0,led[5]);
    neopixel(0,0,led[6]);
    neopixel(0,0,led[7]);
    neopixel(0,0,led[8]);
    neopixel(0,0,led[9]);
}

void main(void) {
    configuro();
    neopixel(0,0,0);
    __delay_ms(1);
    while(1){
        tira_neopixel(led_uno);
        __delay_ms(15);
        tira_neopixel(led_dos);
        __delay_ms(15);
        tira_neopixel(led_tres);
        __delay_ms(15);
        tira_neopixel(led_cuatro);
        __delay_ms(15);
        tira_neopixel(led_cinco);
        __delay_ms(15);
        tira_neopixel(led_seis);
        __delay_ms(15);
        tira_neopixel(led_siete);
        __delay_ms(15);
        tira_neopixel(led_ocho);
        __delay_ms(15);
        tira_neopixel(led_nueve);
        __delay_ms(15);
        tira_neopixel(led_diez);
        __delay_ms(15);
        tira_neopixel(led_nueve);
        __delay_ms(15);
        tira_neopixel(led_ocho);
        __delay_ms(15);
        tira_neopixel(led_siete);
        __delay_ms(15);
        tira_neopixel(led_seis);
        __delay_ms(15);
        tira_neopixel(led_cinco);
        __delay_ms(15);
        tira_neopixel(led_cuatro);
        __delay_ms(15);
        tira_neopixel(led_tres);
        __delay_ms(15);
        tira_neopixel(led_dos);
        __delay_ms(15);
      
        tira_neopixel2(led_uno);
        __delay_ms(15);
        tira_neopixel2(led_dos);
        __delay_ms(15);
        tira_neopixel2(led_tres);
        __delay_ms(15);
        tira_neopixel2(led_cuatro);
        __delay_ms(15);
        tira_neopixel2(led_cinco);
        __delay_ms(15);
        tira_neopixel2(led_seis);
        __delay_ms(15);
        tira_neopixel2(led_siete);
        __delay_ms(15);
        tira_neopixel2(led_ocho);
        __delay_ms(15);
        tira_neopixel2(led_nueve);
        __delay_ms(15);
        tira_neopixel2(led_diez);
        __delay_ms(15);
        tira_neopixel2(led_nueve);
        __delay_ms(15);
        tira_neopixel2(led_ocho);
        __delay_ms(15);
        tira_neopixel2(led_siete);
        __delay_ms(15);
        tira_neopixel2(led_seis);
        __delay_ms(15);
        tira_neopixel2(led_cinco);
        __delay_ms(15);
        tira_neopixel2(led_cuatro);
        __delay_ms(15);
        tira_neopixel2(led_tres);
        __delay_ms(15);
        tira_neopixel2(led_dos);
        __delay_ms(15);
        tira_neopixel3(led_uno);
        __delay_ms(15);
        tira_neopixel3(led_dos);
        __delay_ms(15);
        tira_neopixel3(led_tres);
        __delay_ms(15);
        tira_neopixel3(led_cuatro);
        __delay_ms(15);
        tira_neopixel3(led_cinco);
        __delay_ms(15);
        tira_neopixel3(led_seis);
        __delay_ms(15);
        tira_neopixel3(led_siete);
        __delay_ms(15);
        tira_neopixel3(led_ocho);
        __delay_ms(15);
        tira_neopixel3(led_nueve);
        __delay_ms(15);
        tira_neopixel3(led_diez);
        __delay_ms(15);
        tira_neopixel3(led_nueve);
        __delay_ms(15);
        tira_neopixel3(led_ocho);
        __delay_ms(15);
        tira_neopixel3(led_siete);
        __delay_ms(15);
        tira_neopixel3(led_seis);
        __delay_ms(15);
        tira_neopixel3(led_cinco);
        __delay_ms(15);
        tira_neopixel3(led_cuatro);
        __delay_ms(15);
        tira_neopixel3(led_tres);
        __delay_ms(15);
        tira_neopixel3(led_dos);
        __delay_ms(15);        
    }
}

