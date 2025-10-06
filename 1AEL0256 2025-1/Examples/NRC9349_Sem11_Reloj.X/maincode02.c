/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 9 de junio de 2025, 02:08 PM
 */

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

//variables globales para el reloj
unsigned char   horas=15, minutos=54,
                segundos=0, centesimas=0;

void configuro(void){
    //configuracion del modulo de oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuraciuon de las E/S
    //configuración del PWM con el CCP2
    TRISFbits.TRISF0 = 0;   //RF0 como salida
    ANSELFbits.ANSELF0 = 0; //RF0 como digital
    RF0PPS = 0x16;      //señal de PWM del CCP2 sale por RF0
    T2PR = 98;          //Periodo de PWM a 5KHz
    CCP2CON = 0x9C;      //CCP2 ON, just izquierda, PWM mode
    CCPR2H = 49;
    CCPR2L = 0;         //duty cycle a 50%
    T2CLKCON = 0x01;    //TMR2 con FOSC/4
    T2CON = 0xC0;       //TMR2 ON, PSC 1:16
    //configuracion del ADC
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogica
    ADCON0bits.ADFM = 0;          //ADC just izquierda
    ADCON0bits.CS = 1;          //ADCRC como fuente de reloj
    ADPCH = 0x00;               //canal de lectura RA0
    ADCON0bits.ADON = 1;          //ADC enabled
    //configuracion del TMR1
    T1CLK = 0x01;           //TMR1 source FOSC/4
    T1CON = 0x33;           //TMR1 ON, PSC 1:8, RD16=1
    //configuracion del CCP1 en modo comparacion para TMR1
    CCP1CON = 0x8B;          //CCP1 ON, compare mode rst al TMR1
    CCPR1H = 0x27;
    CCPR1L = 0x10;          //valor de comparacion 10000
    //configuracion de las INTs
    PIE3bits.CCP1IE = 1;        //CCP1IE enabled
    PIR3bits.CCP1IF = 0;        //bajamos la bandera CCP1IF
    INTCON0bits.GIE = 1;        //global interrupts enabled
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(16);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void pantallazo(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Ejemplo de reloj",16);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("UPC Sem11 2025-1",16);
    __delay_ms(3000);
    BORRAR_LCD();
}

void ajuste_backlight(void){
    ADCON0bits.GO = 1;      //inicie la toma de una muestra en el ADC
    while(ADCON0bits.GO == 1);  //esperar a que termine de convertir
    CCPR2H = ADRESH;
}

void visualizacion_hora(void){
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Hora actual:",12);
    POS_CURSOR(2,2);
    ENVIA_CHAR((horas/10) + 0x30);
    ENVIA_CHAR((horas%10) + 0x30);
    ENVIA_CHAR(':');
    ENVIA_CHAR((minutos/10) + 0x30);
    ENVIA_CHAR((minutos%10) + 0x30);
    ENVIA_CHAR(':');
    ENVIA_CHAR((segundos/10) + 0x30);
    ENVIA_CHAR((segundos%10) + 0x30);
    ENVIA_CHAR(':');
    ENVIA_CHAR((centesimas/10) + 0x30);
    ENVIA_CHAR((centesimas%10) + 0x30);    
}

void main(void) {
    configuro();
    lcd_init();
    pantallazo();
    while(1){
        ajuste_backlight();
        visualizacion_hora();
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