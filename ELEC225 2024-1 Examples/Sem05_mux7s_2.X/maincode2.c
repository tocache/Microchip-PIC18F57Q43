#include <xc.h>
#include <string.h>
#include "cabecera.h"
#define _XTAL_FREQ 8000000UL

unsigned char decod[] = {0x77,0x7C,0x39,0x5E,0x79,0x71,0x6F,0x74,0x30,0x1E,0x76,
                        0x38,0x15,0x54,0x3F,0x73,0x67,0x50,0x6D,0x78,0x3E,0x1C,
                        0x2A,0x76,0x6E,0x5B};

unsigned char mensaje[]={"      ELECTRONICA     "};
unsigned char decodificado[];
unsigned int cantidad;
unsigned char indice = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x03;
    OSCEN = 0x40;
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISB = 0xC0;
    ANSELB = 0xC0;
    ANSELE = 0xFC;
    WPUE = 0x03;
    T0CON0 = 0x90;
    T0CON1 = 0x43;
    INTCON0bits.GIE = 1;
    PIE3bits.TMR0IE = 1;
}

void decodificacion(void){
    cantidad = strlen(mensaje);
    unsigned x_var;
    for(x_var=0;x_var<cantidad;x_var++){
        if(mensaje[x_var] == 0x20){
            decodificado[x_var] = 0x00;
        }
        else{
            decodificado[x_var] = decod[mensaje[x_var]-0x41];
        }
    }
}

void multiplexacion(void){
    LATD = decodificado[indice];
    LATBbits.LATB0 = 1;
    __delay_ms(2);
    LATBbits.LATB0 = 0;
    LATD = decodificado[indice+1];
    LATBbits.LATB1 = 1;
    __delay_ms(2);
    LATBbits.LATB1 = 0;
    LATD = decodificado[indice+2];
    LATBbits.LATB2 = 1;
    __delay_ms(2);
    LATBbits.LATB2 = 0;
    LATD = decodificado[indice+3];
    LATBbits.LATB3 = 1;
    __delay_ms(2);
    LATBbits.LATB3 = 0;
    LATD = decodificado[indice+4];
    LATBbits.LATB4 = 1;
    __delay_ms(2);
    LATBbits.LATB4 = 0;
    LATD = decodificado[indice+5];
    LATBbits.LATB5 = 1;
    __delay_ms(2);
    LATBbits.LATB5 = 0;
}

void main(void) {
    configuro();
    while(1){
        multiplexacion();
    }
}

void __interrupt(irq(TMR0)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0;
    if(indice == 16){
        indice = 0;
    }
    else{
        indice++;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}