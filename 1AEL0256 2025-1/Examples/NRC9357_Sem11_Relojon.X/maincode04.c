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

unsigned char valor_ADC=0;
unsigned char horas=11,minutos=50,
        segundos=0,centesimas=0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //conf las E/S
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
    ADCON0bits.ADFM = 0;
    //conf de pwm
    RF0PPS = 0x16;
    T2PR = 98;
    CCP2CON = 0x9C;
    CCPR2H = 49;
    CCPR2L = 0;
    T2CLKCON = 0x01;
    T2CON = 0xC0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 1;
    //conf del TMR1 con CCP1 para RTC
    T1CLK = 0x01;
    T1CON = 0x33;
    CCP1CON = 0x8B;
    CCPR1H = 0x27;
    CCPR1L = 0x10;
    PIE3bits.CCP1IE = 1;
    PIR3bits.CCP1IF = 0;
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

void control_backlight(void){
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE == 1);
    valor_ADC = ADRESH;
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Canal ANA0:", 11);
    ENVIA_CHAR((valor_ADC / 1000) + 0x30);
    ENVIA_CHAR(((valor_ADC % 1000) / 100) + 0x30);
    ENVIA_CHAR(((valor_ADC % 100) / 10) + 0x30);
    ENVIA_CHAR((valor_ADC % 10) + 0x30);
    CCPR2H = ADRESH;    
}

void mostrar_reloj(void){
    POS_CURSOR(2,0);
    ENVIA_CHAR(0);
    ENVIA_CHAR(' ');
    ENVIA_CHAR((horas / 10) + 0x30);
    ENVIA_CHAR((horas % 10) + 0x30);
    ENVIA_CHAR(':');
    ENVIA_CHAR((minutos / 10) + 0x30);
    ENVIA_CHAR((minutos % 10) + 0x30);
    ENVIA_CHAR(':');
    ENVIA_CHAR((segundos / 10) + 0x30);
    ENVIA_CHAR((segundos % 10) + 0x30);
    ENVIA_CHAR(':');
    ENVIA_CHAR((centesimas / 10) + 0x30);
    ENVIA_CHAR((centesimas % 10) + 0x30);
}
void main(void) {
    configuro();
    lcd_init();
    splash_screen();
    while(1){
        control_backlight();
        mostrar_reloj();
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    CCP2CONbits.CCP2EN = ~CCP2CONbits.CCP2EN; 
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;
    if(centesimas == 99){
        centesimas = 0;
        if(segundos == 59){
            segundos = 0;
            if(minutos == 59){
                minutos = 0;
                if(horas == 23){
                    horas = 0;
                }
                else{
                    horas++;
                }
            }
            else{
                minutos++;
            }
        }
        else{
            segundos++;
        }
    }
    centesimas++;
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}
