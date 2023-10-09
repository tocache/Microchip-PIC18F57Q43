#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;     //HFINTOSC selected
    OSCFRQ = 0x02;      //HFINTOSC a 4MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    TRISEbits.TRISE0 = 0;   //RE0 como salida
    ANSELEbits.ANSELE0 = 0; //RE0 como digital
    LATEbits.LATE0 = 1;     //LCD backlight ON
}

void main(void) {
    configuro();            //llamado a funcion configuro
    LCD_INIT();             //Inicializacion del LCD
    while(1){
        POS_CURSOR(1,0);        //Posicion del curso arriba a la izquierda
        ESCRIBE_MENSAJE2("Hola mundo UPAO!");
    }
}
