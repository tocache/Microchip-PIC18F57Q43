#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

unsigned char texto[] = {"    UPAO   "};
//0x55,0x50,0x41,0x4F en ascii
	                     //A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z  
unsigned char decod[] = {0x77,0x7C,0x39,0x5E,0x79,0x71,0x6F,0x74,0x30,0x1E,0x76,0x38,0x15,0x54,0x3F,0x73,0x67,0x50,0x6D,0x78,0x3E,0x1C,0x2A,0x76,0x6E,0x5B};
unsigned char desplaza = 0;

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HFINTOSC habilitado
    TRISB = 0x80;                   //RB6 al RB0 salidas
    ANSELB = 0x80;                  //RB6 al RB0 digitales
    TRISA = 0xF0;                   //RA3 al RA0 salidas
    ANSELA = 0xF0;                  //RA3 al RA0 digitales
    TRISDbits.TRISD0 = 1;           //RD0 entrada
    ANSELDbits.ANSELD0 = 0;         //RD0 digital
    WPUDbits.WPUD0 = 1;             //pull-up en RD0 activada
    LATA = 0xFF;                    //condicion inicial de la multiplexacion
    T0CON0 = 0x90;                  //TMR0 enabled, 16bit, post 1:1
    T0CON1 = 0x52;                  //FOSC/4, pre 1:4
    TMR0H = 0x3C;
    TMR0L = 0xB0;
}

void multiplex(void){
    LATB = decod[texto[0+desplaza]-0x41];
    LATA = 0xFE;
    __delay_ms(20);
    LATA = 0xFF;
    LATB = decod[texto[1+desplaza]-0x41];
    LATA = 0xFD;
    __delay_ms(20);
    LATA = 0xFF;
    LATB = decod[texto[2+desplaza]-0x41];
    LATA = 0xFB;
    __delay_ms(20);
    LATA = 0xFF;
    LATB = decod[texto[3+desplaza]-0x41];
    LATA = 0xF7;
    __delay_ms(20);
    LATA = 0xFF;
}

void main(void) {
    configuro();
    while(1){
        while(PIR3bits.TMR0IF == 0){
            multiplex();
        }
        PIR3bits.TMR0IF = 0;
        TMR0H = 0x3C;
        TMR0L = 0xB0;
        if(desplaza == 7){
            desplaza = 0;
        }
        else{
            desplaza++;
        }
    }
    
}
