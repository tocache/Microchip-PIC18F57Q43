/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 9 de junio de 2025, 06:03 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //conf modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCENbits.HFOEN = 1;
    //conf de las E/S
    //conf del CCP2 y TMR2
    RF0PPS = 0x16;      //CCP2 sale por RF0
    T2PR = 98;          //TMR2 a 5KHz (200us)
    CCP2CON = 0x9C;     //CCP2 Enabled, PWM just izq
    CCPR2H = 49;        //Duty Cycle a 50%
    CCPR2L = 0;
    T2CLKCON = 0x01;    //TMR2 src FOSC/4
    T2CON = 0xC0;       //TMR2 enabled, PSC 1:16
    TRISFbits.TRISF0 = 0;   //RF0 salida
    ANSELFbits.ANSELF0 = 0; //RF0 digital
    //conf del ADC
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogico
    ADCON0bits.ADFM = 0;    //just izquierda
    ADCON0bits.CS = 1;       //ADC src ADCRC
    ADPCH = 0x00;           //RA0 va a leerse
    ADCON0bits.ADON = 1;    //ADC enabled
    //conf el TMR1 para RTC
    T1CLK = 0x01;       //TMR1 src FOSC/4
    T1CON = 0x33;       //TMR1 psc 1:8, TMR1 ON
    //conf del CCP1 para RTC del TMR1
    CCP1CON = 0x8B;  //CCP1 en compare y reset TMR1
    CCPR1H = 0x27;
    CCPR1L = 0x10;  //valor de comparación 10000
    //conf las interrupts
    PIE3bits.CCP1IE = 1;        //CCP1IE enabled
    PIR3bits.CCP1IF = 0;        //bajamos bandera CCP1IF
    INTCON0bits.GIE = 1;        //global interrupts enabled
}

const unsigned char reloj[]={0x1B,0x1B,0x0E,
                    0x15,0x15,0x17,0x11,0x0E};
unsigned char horas=19,minutos=43,segundos=0,centesimas=0;

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(21);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    GENERACARACTER(reloj, 0);
}

void splash_screen(void){
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE("Segundo turno", 13);
    POS_CURSOR(2,1);
    ESCRIBE_MENSAJE("Micro NRC9350", 13);
    __delay_ms(2000);
    BORRAR_LCD();
    POS_CURSOR(1,0);
    ENVIA_CHAR(0);
}

void control_backlight(void){
    ADCON0bits.GO_nDONE = 1;    //toma una muestra ADC
    while(ADCON0bits.GO_nDONE == 1);    //espera a que termine
    CCPR2H = ADRESH;    
}

void main(void) {
    configuro();
    lcd_init();
    splash_screen();
    while(1){
        control_backlight();
        POS_CURSOR(1,2);
        ESCRIBE_MENSAJE("Hora actual:", 12);
        POS_CURSOR(2,1);
        ENVIA_CHAR(0);
        ENVIA_CHAR(' ');
        ENVIA_CHAR((horas/10)+0x30);
        ENVIA_CHAR((horas%10)+0x30);
        ENVIA_CHAR(':');
        ENVIA_CHAR((minutos/10)+0x30);
        ENVIA_CHAR((minutos%10)+0x30);
        ENVIA_CHAR(':');
        ENVIA_CHAR((segundos/10)+0x30);
        ENVIA_CHAR((segundos%10)+0x30);
        ENVIA_CHAR(':');
        ENVIA_CHAR((centesimas/10)+0x30);
        ENVIA_CHAR((centesimas%10)+0x30);
    }
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
    else{
        centesimas++;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
    
}