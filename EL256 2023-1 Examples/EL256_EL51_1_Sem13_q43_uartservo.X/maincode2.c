#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    TRISE = 0xF8;
    ANSELE = 0xF8;
    TRISD = 0x0F;
    ANSELD = 0x0F;
    //El boton en RB0 que sea la INT0
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    INTCON0bits.INT0EDG = 0;
    INT0PPS = 0x08;             //remapeado INT0 hacia RB0
    PIE1bits.INT0IE = 1;
    //El boton en RB4 que sea la INT1
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSELB4 = 0;
    WPUBbits.WPUB4 = 1;
    INTCON0bits.INT1EDG = 0;
    INT1PPS = 0x0C;             //remapeado INT1 hacia RB4
    PIE6bits.INT1IE = 1;        //habilitador de INT1 activao
    INTCON0bits.GIE = 1;        //habilitador global de interrupciones activado
    //configuracion para enviar por el UART
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    RF0PPS = 0x2C;              //PPS asignacion de U5TX hacia RF0
    U5BRGH = 0;
    U5BRGL = 25;                //BRG trabajando a 9600
    U5CON0 = 0x20;              //BRGS=0, TXEN=1, modo async 8 bit
    U5CON1 = 0x80;              //Serial port enabled
    U5CON2 = 0x00;              //por seaca
    LCD_INIT();
}

void U5_Sendbyte(unsigned char dato){
    U5TXB = dato;
    while(U5ERRIRbits.TXMTIF == 0);
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola Mundo!");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Micro semana 13");
    __delay_ms(2000);
    BORRAR_LCD();
}


void main(void) {
    configuro();
    pantallazo();
    while(1){
        
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    U5_Sendbyte('H');
    U5_Sendbyte('o');
    U5_Sendbyte('l');
    U5_Sendbyte('a');
    pantallazo();
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    U5_Sendbyte('m');
    U5_Sendbyte('u');
    U5_Sendbyte('n');
    U5_Sendbyte('d');
    U5_Sendbyte('o');
    pantallazo();
}