/*
 * File:   maincode01.c
 * Author: upao
 *
 * Created on 9 de septiembre de 2024, 10:04 AM
 */
#include <xc.h>
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    //configuracion de la fuente de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISDbits.TRISD0 = 0;       //RD0 como salida
    ANSELDbits.ANSELD0 = 0;     //RD0 como digital
    LATDbits.LATD0 = 0;
    //configuracion del Timer0
    TMR0H = 20;
    TMR0L = 0;          //Valor inicial de la cuenta
    T0CON0 = 0x80;      //Timer0 enabled, 8bit mode, POSTS 1:1
    T0CON1 = 0x4F;      //CLK src FOSC/4, PRESC 1:32768
    PIR3bits.TMR0IF = 0;        //bajamos la bandera
}

void main(void) {
    configuro();
    while(1){
        if(PIR3bits.TMR0IF == 1){
            PIR3bits.TMR0IF = 0;        //bajamos la bandera
            LATDbits.LATD0 = ~LATDbits.LATD0;
/*            if(LATDbits.LATD0 == 0){
                LATDbits.LATD0 = 1;
            }
            else{
                LATDbits.LATD0 = 0;
            }*/
        }
    }
}
