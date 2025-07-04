#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

const unsigned char logo_reloj[] = {
  0x1B,
  0x1B,
  0x0E,
  0x15,
  0x17,
  0x11,
  0x0E,
  0x11
};

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //conf las E/S
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 1;
    LATFbits.LATF0 = 1;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    //conf adc
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    ADCON0bits.CS = 1;
    ADREF = 0x00;
    ADPCH = 0x00;
    ADCON0bits.ADON = 1;
    ADCON0bits.ADFM = 1;
    //conf la INT0
    INT0PPS = 0x08;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    INTCON0bits.INT0EDG = 0;
    INTCON0bits.GIE = 1;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(logo_reloj,0);
}

void splash_screen(void){
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE("RELOJ 2025-1 ",13);
    ENVIA_CHAR(0);
    POS_CURSOR(2,1);
    ESCRIBE_MENSAJE("UPC MICROBIOS",13);
    __delay_ms(3000);
    BORRAR_LCD();
}

unsigned int valor_ADC=0;

void main(void) {
    configuro();
    lcd_init();
    splash_screen();
    while(1){
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE == 1);
        valor_ADC = (ADRESH << 8) + ADRESL;
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE("Canal ANA0:", 11);
        ENVIA_CHAR((valor_ADC / 1000) + 0x30);
        ENVIA_CHAR(((valor_ADC % 1000) / 100) + 0x30);
        ENVIA_CHAR(((valor_ADC % 100) / 10) + 0x30);
        ENVIA_CHAR((valor_ADC % 10) + 0x30);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    LATFbits.LATF0 = ~LATFbits.LATF0;
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}
