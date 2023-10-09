#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char opcion = 0;       //para las opciones de duty cycle

void configuro(void){
    OSCCON1 = 0x60;     //HFINTOSC selected
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de puertos
    TRISE = 0xFF;       //RE1 y RE0 como entradas
    ANSELE = 0xFC;      //RE1 y RE0 como digitales
    WPUE = 0x03;        //RE1 y RE0 pullups 
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    //configuracion del Timer0
    T0CON0 = 0x90;      //TMR0 ON, 16bit, POSTS 1:1
    T0CON1 = 0x70;      //TMR0 HFINTOSC, SYNC, PRES 1:1
}

void main(void) {
    configuro();            //llamado a funcion configuro
    LCD_INIT();             //Inicializacion del LCD
    POS_CURSOR(1,0);        //Posicion del curso arriba a la izquierda
    ESCRIBE_MENSAJE2("5KHz PWM Gen");
    while(1){
        opcion = (PORTE & 0x03);
        switch(opcion){
            case 0:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Duty Cycle 10% ");
                //TON
                LATBbits.LATB0 = 1;
                TMR0H = 0xFF;
                TMR0L = 0xB0;
                while(PIR3bits.TMR0IF == 0);
                PIR3bits.TMR0IF = 0;
                //TOF
                LATBbits.LATB0 = 0;
                TMR0H = 0xFD;
                TMR0L = 0x30;
                while(PIR3bits.TMR0IF == 0);
                PIR3bits.TMR0IF = 0;
                break;
            case 1:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Duty Cycle 30% ");
                //TON
                LATBbits.LATB0 = 1;
                TMR0H = 0xFF;
                TMR0L = 0x10;
                while(PIR3bits.TMR0IF == 0);
                PIR3bits.TMR0IF = 0;
                //TOF
                LATBbits.LATB0 = 0;
                TMR0H = 0xFD;
                TMR0L = 0xD0;
                while(PIR3bits.TMR0IF == 0);
                PIR3bits.TMR0IF = 0;
                break;
            case 2:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Duty Cycle 80% ");
                //TON
                LATBbits.LATB0 = 1;
                TMR0H = 0xFD;
                TMR0L = 0x80;
                while(PIR3bits.TMR0IF == 0);
                PIR3bits.TMR0IF = 0;
                //TOF
                LATBbits.LATB0 = 0;
                TMR0H = 0xFF;
                TMR0L = 0x60;
                while(PIR3bits.TMR0IF == 0);
                PIR3bits.TMR0IF = 0;
                break;
            case 3:
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE2("Duty Cycle 100%");
                LATBbits.LATB0 = 1;
                break;
        }
    }
}




//Subir evidencia de video a la carpeta compartida con nombre de archivo:
//[codigo]_[primer apellido]_[primer nombre]_Sem5_As01.mp4
//ejemplo de nombre: 000030619_Lau_Kalun_Sem5_As01.mp4