/*
 * File:   maincode.c
 * Author: upao
 *
 * Created on 2 de septiembre de 2024, 10:34 AM
 */

#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL
#define time 1

unsigned char palabra_upao[]={0x3E, 0x73, 0x77, 0x3F};
unsigned char palabra_chip[]={0x39, 0x76, 0x30, 0x73};
unsigned char palabra_elec[]={0x79, 0x38, 0x79, 0x39};
unsigned char indicador = 0;

void configuro(void){
    //configuracion de la fuente de reloj
    OSCCON1 = 0x60;     //Fuente:HFINTOSC, DIV a 1:1
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    // configuracion de las E/S
    TRISD = 0x00;       //RD como salida
    ANSELD = 0x00;      //RD como digital
    TRISB = 0xF0;       //RB[3:0] como salidas
    ANSELB = 0xF0;      //RB[3:0] como digitales
    TRISF = 0xFF;       //RF[1:0] como entradas
    ANSELF = 0xFC;      //RF[0:1] como digitales
    WPUF = 0x03;        //RF[0:1] pullup activadas
    //configuracion del Timer0
    TMR0H = 20;
    TMR0L = 0;          //Valor inicial de la cuenta
    T0CON0 = 0x80;      //Timer0 enabled, 8bit mode, POSTS 1:1
    T0CON1 = 0x4F;      //CLK src FOSC/4, PRESC 1:32768
    PIR3bits.TMR0IF = 0;        //bajamos la bandera
    //condicion inicial
    LATB = 0x00;        //RB[3:0]=0x00
}

void multiplexacion1(void){
    LATD = palabra_upao[0];
    LATBbits.LATB0 = 1;
    __delay_ms(time);
    LATBbits.LATB0 = 0;
    LATD = palabra_upao[1];
    LATBbits.LATB1 = 1;
    __delay_ms(time);
    LATBbits.LATB1 = 0;
    LATD = palabra_upao[2];
    LATBbits.LATB2 = 1;
    __delay_ms(time);
    LATBbits.LATB2 = 0;
    LATD = palabra_upao[3];
    LATBbits.LATB3 = 1;
    __delay_ms(time);
    LATBbits.LATB3 = 0;
}

void multiplexacion2(void){
    LATD = palabra_chip[0];
    LATBbits.LATB0 = 1;
    __delay_ms(time);
    LATBbits.LATB0 = 0;
    LATD = palabra_chip[1];
    LATBbits.LATB1 = 1;
    __delay_ms(time);
    LATBbits.LATB1 = 0;
    LATD = palabra_chip[2];
    LATBbits.LATB2 = 1;
    __delay_ms(time);
    LATBbits.LATB2 = 0;
    LATD = palabra_chip[3];
    LATBbits.LATB3 = 1;
    __delay_ms(time);
    LATBbits.LATB3 = 0;
}

void multiplexacion3(void){
    LATD = palabra_elec[0];
    LATBbits.LATB0 = 1;
    __delay_ms(time);
    LATBbits.LATB0 = 0;
    LATD = palabra_elec[1];
    LATBbits.LATB1 = 1;
    __delay_ms(time);
    LATBbits.LATB1 = 0;
    LATD = palabra_elec[2];
    LATBbits.LATB2 = 1;
    __delay_ms(time);
    LATBbits.LATB2 = 0;
    LATD = palabra_elec[3];
    LATBbits.LATB3 = 1;
    __delay_ms(time);
    LATBbits.LATB3 = 0;
}

void main(void) {
    configuro();
    while(1){
        if(PIR3bits.TMR0IF == 1){
            PIR3bits.TMR0IF = 0;        //bajamos la bandera
            if(indicador == 2){
                indicador = 0;
            }
            else{
                indicador++;
            }
        }
        switch(indicador){
            case 0:
                multiplexacion1();
                break;
            case 1:
                multiplexacion2();
                break;
            case 2:
                multiplexacion3();
                break;
        }
    }
}
