#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char reloj_1[]={0x0C,0x1E,0x1C,0x14,
                         0x07,0x0C,0x1E,0x13};
unsigned char reloj_2[]={0x06,0x0F,0x07,0x05,
                         0x1C,0x06,0x03,0x07};
unsigned char reloj_3[]={0x11,0x11,0x10,0x18,
                         0x0C,0x07,0x0C,0x1E};
unsigned char reloj_4[]={0x1D,0x11,0x01,0x03,
                         0x06,0x1C,0x06,0x0F};
unsigned char ADC_value = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCENbits.HFOEN = 1;
    //conf adc
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    ADREF = 0x00;
    ADPCH = 0x00;
    ADCON0bits.ADON = 1;
    ADCON0bits.ADFM = 0; //just izq
    //conf pwm
    RF0PPS = 0x16;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    T2PR = 98;
    CCP2CON = 0x9C;
    CCPR2H = 49;
    CCPR2L = 0;
    T2CLKCON = 0x01;
    T2CON = 0xC0;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(21);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(reloj_1, 0);
    GENERACARACTER(reloj_2, 1);
    GENERACARACTER(reloj_3, 2);
    GENERACARACTER(reloj_4, 3);
}

void pantallon(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Reloj UPCino ", 13);
    ENVIA_CHAR(0);
    ENVIA_CHAR(1);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Micro 2025-1 ", 13);
    ENVIA_CHAR(2);
    ENVIA_CHAR(3);
    __delay_ms(4000);
    BORRAR_LCD();
}

void main(void) {
    configuro();
    lcd_init();
    pantallon();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        ADC_value = ADRESH;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("ANA0:", 5);
        ENVIA_CHAR((ADC_value/100)+0x30);
        ENVIA_CHAR(((ADC_value%100)/10)+0x30);
        ENVIA_CHAR((ADC_value%10)+0x30);
        CCPR2H = ADRESH;
    }
}
