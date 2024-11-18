/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 11 de noviembre de 2024, 09:35 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LIB_UART.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char menu_activo = 0;      //0 es menu principal, 1 es menu LCD

void configuro(void){
    //conf de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configurar las E/S
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;
    //inicializacion del UART1
    U1_INIT(BAUD_57600);
    //configuracion de las interrupciones
    PIE4bits.U1RXIE = 1;
    PIR4bits.U1RXIF = 0;
    INTCON0bits.GIE = 1; 
    //inicializar el LCD
    I2C_LCD_INIT();
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
    TRISFbits.TRISF2 = 0;
    ANSELFbits.ANSELF2 = 0;
    RF2PPS = 0x01;      //CLC1out connected to RF2    
}

void neopixel(unsigned char r, unsigned char g, unsigned char b){
    SPI1TXB = r;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = g;
    while(!SPI1STATUSbits.TXBE);
    SPI1TXB = b;
    while(!SPI1STATUSbits.TXBE);
}

void vis_menu_P(void){
    U1_STRING_SEND("*******************************");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("* Bienvenidos a la aplicacion *");
    U1_NEWLINE();
    U1_STRING_SEND("*    de Neopixel WS2812       *");
    U1_NEWLINE();
    U1_STRING_SEND("* Desarrollado por Kalun Lau  *");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("*      .--.                   *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |__| .-------.         *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |=.| |.-----.|         *");  
    U1_NEWLINE();
    U1_STRING_SEND("*      |--| || KCK ||         *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |  | |'-----'|         *");
    U1_NEWLINE();
    U1_STRING_SEND("*      |__|~')_____('         *");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("* Elija opcion:               *");
    U1_NEWLINE();
    U1_STRING_SEND("* (1) LED azul                *");
    U1_NEWLINE();
    U1_STRING_SEND("* (2) LED verde               *");
    U1_NEWLINE();
    U1_STRING_SEND("* (3) LED rojo                *");
    U1_NEWLINE();
    U1_STRING_SEND("* (4) LED apagado             *");
    U1_NEWLINE();
    U1_STRING_SEND("* (m) Mostrar el menu         *");
    U1_NEWLINE();
    U1_STRING_SEND("*                             *");
    U1_NEWLINE();
    U1_STRING_SEND("*******************************");
    U1_NEWLINE();
}

void main(void) {
    configuro();
    __delay_ms(1000);    
    vis_menu_P();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Neopixel");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Apagado!");
    neopixel(0,0,0);
    while(1){
        
    }
}

//atencion al ingreso desde el teclado
void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    switch(U1RXB){
        case '1':
            U1_STRING_SEND("LED azul!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Azul!   ");
            neopixel(0,0,255);
            break;
        case '2':
            U1_STRING_SEND("LED verde!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Verde!  ");
            neopixel(255,0,0);
            break;
        case '3':
            U1_STRING_SEND("LED rojo!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Rojo!   ");
            neopixel(0,255,0);
            break;
        case '4':
            U1_STRING_SEND("LED apagado!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Apagado!");
            neopixel(0,0,0);
            break;            
        case 'm':
            vis_menu_P();
            break;
        default:
            U1_STRING_SEND("Opcion invalida, intente de nuevo");
            U1_NEWLINE();
    }

}

void __interrupt(irq(default)) default_ISR(void){
    
}