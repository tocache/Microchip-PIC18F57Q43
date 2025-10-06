#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char mensaje = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //conf de la INT2
    INT2PPS = 0x0A;
    TRISBbits.TRISB2 = 1;
    ANSELBbits.ANSELB2 = 0;
    PIE10bits.INT2IE = 1;
    PIR10bits.INT2IF = 0;
}

void main(void) {
    configuro();
    I2C_LCD_INIT();
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Hola UPCino");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Micro 2025-1");
    __delay_ms(2000);
    I2C_BORRAR_LCD();
    INTCON0bits.GIE = 1;
    while(1){
        switch(mensaje){
            case 0:
                I2C_POS_CURSOR(1,0);
                I2C_ESCRIBE_MENSAJE2("Mensaje 0");
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Mecatronica     ");
                break;
            case 1:
                I2C_POS_CURSOR(1,0);
                I2C_ESCRIBE_MENSAJE2("Mensaje 1");
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Electronica    " );
                break;
            case 2:
                I2C_POS_CURSOR(1,0);
                I2C_ESCRIBE_MENSAJE2("Mensaje 2");
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Biomedica     "  );
                break;
            case 3:
                I2C_POS_CURSOR(1,0);
                I2C_ESCRIBE_MENSAJE2("Mensaje 3");
                I2C_POS_CURSOR(2,0);
                I2C_ESCRIBE_MENSAJE2("Corte y Confecc" );
                break;
        }
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    if(mensaje == 3){
        mensaje = 0;
    }
    else{
        mensaje++;
    }
}