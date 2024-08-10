#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

void configuro(void){
    OSCCON1 = 0x60;         //NOSC=HFINTOSC NDIV1:1
    OSCFRQ = 0x05;          //HFINTOSC 16MHz
    OSCEN = 0x40;           //HFINTOSC enabled
}

void main(void) {
    configuro();            //calling configuro function
    LCD_INIT();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola UPCINO");    //new function
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("meca y elec");    //new function
    while(1){               //do it forever
    }
}
