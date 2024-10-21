/*
 * File:   maincode01.c
 * Author: docente_G
 *
 * Created on 30 de septiembre de 2024, 11:21 AM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"

#define _XTAL_FREQ 32000000UL

void configuro(void){
    //fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    LCD_INIT();         //Iniciamos el LCD
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("   Hola mundo   ");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Ing. Elec-Mecatr");
    while(1){
        
    }
}
