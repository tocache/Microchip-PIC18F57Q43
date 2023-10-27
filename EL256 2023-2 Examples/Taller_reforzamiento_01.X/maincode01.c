#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 16000000UL

unsigned char dutycycle = 0;
unsigned char centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC y PSC 1:1
    OSCFRQ = 0x05;      //HFINTOSC a 16MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISBbits.TRISB0 = 1;   //RB0 entrada
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup enabled
    TRISBbits.TRISB2 = 1;   //RB0 entrada
    ANSELBbits.ANSELB2 = 0; //RB0 digital
    WPUBbits.WPUB2 = 1;     //RB0 pullup enabled
    //configuracion de las interrupciones
    PIE1bits.INT0IE = 1;        //INT0 enabled
    PIE10bits.INT2IE = 1;       //INT2 enabled
    INTCON0bits.INT0EDG = 0;    //INT0 falling edge detect
    INTCON0bits.INT2EDG = 0;    //INT2 falling edge detect
    PIR1bits.INT0IF = 0;        //INT0 flag en cero
    PIR10bits.INT2IF = 0;       //INT2 flag en cero
    INTCON0bits.GIE = 1;        //global interrupt enabled
    //configuracion de PWM 5KHz y 50%DC
    TRISCbits.TRISC2 = 0;       //RC2 como salida
    ANSELCbits.ANSELC2 = 0;     //RC2 como digital
    T2PR = 49;                  //freq del PWM a 5KHz
    RC2PPS = 0x15;              //asignacion PPS de CCP1 para que salga por RC2
    CCP1CON = 0x9C;              //CCP1 on, PWM mode, left justified
    CCPR1H = 25;
    CCPR1L = 0;                 //duty cycle a 50%
    T2CLKCON = 0x01;            //TMR2 con FOSC/4
    T2CON = 0xC0;               //TMR2 ON pres 1:16 posts 1:1
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(23);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE("PWM Generator", 13);
    while(1){
        POS_CURSOR(2, 1);
        ESCRIBE_MENSAJE("Duty Cycle:", 11);
        convierte(dutycycle);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR('%');
        CCPR1H = dutycycle / 2;
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(dutycycle == 100){
        dutycycle = 100;
    }
    else{
        dutycycle = dutycycle + 10;
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    if(dutycycle == 0){
        dutycycle = 0;
    }
    else{
        dutycycle = dutycycle - 10;
    }
}

