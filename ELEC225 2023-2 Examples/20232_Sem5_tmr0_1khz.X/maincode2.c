#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HTINTOSC habilitado
    TRISBbits.TRISB0 = 0;           //RB0 como salida
    ANSELBbits.ANSELB0 = 0;         //RB0 como digital
    TRISBbits.TRISB4 = 1;           //RB4 como entrada
    ANSELBbits.ANSELB4 = 0;         //RB4 como digital
    WPUBbits.WPUB4 = 1;             //RB$ con pullup activado
    T0CON0 = 0x80;                  //Tmr0 ON, postscaler 1:1
    T0CON1 = 0x42;                  //Source FOSC/4, prescaler 1:4
    TMR0H = 250;                    //Valor de referencia de comparacion
    LCD_INIT();                     //inicializacion del LCD
}

void main(void) {
    configuro();                            //llama a función configuro
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Generador SQRWAV");
    while(1){                               //bucle repetitivo
        if(PORTBbits.RB4 == 0){             //pregunto si presione RB4
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("f:1.00KHz DC:20%");
            LATBbits.LATB0 = 1;             //RB4 en uno (TON)
            TMR0H = 50;                    //TMR0 temporiza 200uS
            while(PIR3bits.TMR0IF == 0);    //pregunto si terminó de temporizar (TMR0IF=1)
            PIR3bits.TMR0IF = 0;            //bajo banderda TMR0IF            
            LATBbits.LATB0 = 0;             //RB4 en cero (TOF)
            TMR0H = 200;                    //TMR0 temporiza 800uS
            while(PIR3bits.TMR0IF == 0);    //pregunto si terminó de temporizar (TMR0IF=1)
            PIR3bits.TMR0IF = 0;            //bajo banderda TMR0IF
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("f:1.00KHz DC:70%");
            LATBbits.LATB0 = 1;             //RB4 en uno (TON)
            TMR0H = 175;                    //TMR0 temporiza 700uS
            while(PIR3bits.TMR0IF == 0);    //pregunto si terminó de temporizar (TMR0IF=1)
            PIR3bits.TMR0IF = 0;            //bajo banderda TMR0IF            
            LATBbits.LATB0 = 0;             //RB4 en cero (TOF)
            TMR0H = 75;                    //TMR0 temporiza 300uS
            while(PIR3bits.TMR0IF == 0);    //pregunto si terminó de temporizar (TMR0IF=1)
            PIR3bits.TMR0IF = 0;            //bajo banderda TMR0IF
        }
    }
}
