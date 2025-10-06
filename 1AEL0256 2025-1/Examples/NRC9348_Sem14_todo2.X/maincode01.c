#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

//declaracion de variables globales
unsigned char lectura_ch0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    //Conf para leer el potenciometro en RA0
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    ADCON0bits.ADFM = 0;
    ADPCH = 0x00;
    ADREF = 0x00;
    ADCON0bits.ADON = 1;
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Sem14 UPC Micro");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ing BioMecaEle ");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        lectura_ch0 = ADRESH;
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC_CH0:");
        I2C_LCD_ESCRIBE_VAR_CHAR(lectura_ch0,3);
    }
}
