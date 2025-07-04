#include <xc.h>
#include "cabecera.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    I2C_LCD_INIT();
    //conf adc para ra0
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.ADCS = 1;
    ADREF = 0x00;
    ADPCH = 0x00;
    ADCON0bits.ADFM = 0;
    ADCON0bits.ADON = 1;
}

void pantallazo(void){
    I2C_POS_CURSOR(1,0);
    I2C_ESCRIBE_MENSAJE2("Micro UPC Sem14 ");
    I2C_POS_CURSOR(2,0);
    I2C_ESCRIBE_MENSAJE2("Ultimo lab :(   ");
    __delay_ms(3000);
    I2C_BORRAR_LCD();
}

unsigned char lectura_ADC_RA0(void){
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE == 1);
    return ADRESH;
}

void main(void) {
    configuro();
    pantallazo();
    while(1){
        I2C_POS_CURSOR(1,0);
        I2C_ESCRIBE_MENSAJE2("ADC-0:");
        I2C_LCD_ESCRIBE_VAR_CHAR(lectura_ADC_RA0(), 3);
        __delay_ms(50);
    }
}
