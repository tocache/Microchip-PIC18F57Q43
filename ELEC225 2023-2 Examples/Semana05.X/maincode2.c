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
    //Para usar el boton integrado como funcion de RESET al módulo
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 con pullup activada
    INT0PPS = 0x0C;         //Redireccion de INT0 hacia RB4
    INTCON0 = 0x80;         //GIE=1, INT0EDG=0
    PIE1 = 0x01;            //INT0IE=1
}

void main(void) {
    configuro();            //llamado a funcion configuro
    LCD_INIT();             //Inicializacion del LCD
    POS_CURSOR(1,0);        //Posicion del curso arriba a la izquierda
    ESCRIBE_MENSAJE2("Hola mundo UPAO!");
    while(1){
        unsigned char x_var;
        for(x_var=0;x_var<16;x_var++){
            POS_CURSOR(2,x_var);
            ENVIA_CHAR(0xDB);
            __delay_ms(100);
        }
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("                ");
    }
}

//Funcion de RESET usando interrupcion externa INT0 e instruccion assembler
void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    asm("RESET");
}

//Subir evidencia de video a la carpeta compartida con nombre de archivo:
//[codigo]_[primer apellido]_[primer nombre]_Sem5_As01.mp4
//ejemplo de nombre: 000030619_Lau_Kalun_Sem5_As01.mp4