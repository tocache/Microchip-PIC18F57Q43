#include<stdio.h>
#include<stdlib.h>
#include "CABECERA.h"
#define _XTAL_FREQ 32000000UL
void CONFIGURACION()
{
    OSCCON1=0x60;//HFINTOSC  DIV 1
    OSCFRQ=0x6; //32MHZ
    OSCEN=0x40;//HABILITAMOS EL HFINTOSC
    TRISF=0;
    TRISC=0;
    ANSELC=0;
    ANSELF=0;
}
unsigned char x[23]={0x8,0x4,0x2,0x1,0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1,0x1,0x2,0x4};																		
unsigned char C,F,J,k;
void COLUMNA(unsigned char a)
{
    if (a==0){J=0xfe;}//0b11111110;}
    if (a==1){J=0xfd;}//0b11111101;}
    if (a==2){J=0xfb;}//0b11111011;}
    if (a==3){J=0xf7;}//0b11110111;}
    if (a==4){J=0xef;}//0b11101111;}
    if (a==5){J=0xdf;}//0b11011111;}
    if (a==6){J=0xbf;}//0b10111111;}
    if (a==7){J=0x7f;}//0b01111111;}
    if (a==8){J=0xff;}//0b01111111;}
    
}
void main (void)
{
    CONFIGURACION();
    while(1)
    {
    for (F=0; F<16; F++)
    {
        for(k=0;k<30;k++)
        {
            for (C=0; C<8; C++)
            {
                LATF=x[C+F];
                COLUMNA(C);
                LATC=J;
                __delay_ms (1);
                LATC=255;        
            }
        }
    }   
    }
    return;
}