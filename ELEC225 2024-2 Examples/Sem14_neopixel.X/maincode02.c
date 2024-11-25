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
#include "LIB_WS2812.h"
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
    //inicializar el WS2812
    WS2812_INIT();
    //port config
    TRISFbits.TRISF3 = 0;   //onboard LED config
    ANSELFbits.ANSELF3 = 0;
    TRISFbits.TRISF2 = 0;
    ANSELFbits.ANSELF2 = 0;
    RF2PPS = 0x01;      //CLC1out connected to RF2    
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
    WS2812_DATA_SEND(0,0,0);
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
            WS2812_DATA_SEND(0,0,255);
            break;
        case '2':
            U1_STRING_SEND("LED verde!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Verde!  ");
            WS2812_DATA_SEND(255,0,0);
            break;
        case '3':
            U1_STRING_SEND("LED rojo!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Rojo!   ");
            WS2812_DATA_SEND(0,255,0);
            break;
        case '4':
            U1_STRING_SEND("LED apagado!");
            U1_NEWLINE();
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("Apagado!");
            WS2812_DATA_SEND(0,0,0);
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
