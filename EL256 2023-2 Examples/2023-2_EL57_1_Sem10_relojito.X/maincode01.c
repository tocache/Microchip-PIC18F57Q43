#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL   //FOSC a 32MHz

unsigned char horas=17, minutos=20, segundos=23, centesimas=56;
unsigned char centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC posts 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion para los botones
    TRISB = 0xFF;       //RB1:RB0 como entradas
    ANSELB = 0xFC;      //RB1:RB0 como digitales
    WPUB = 0x03;        //RB1:RB0 con pullup activado
    //configuracion del Timer1
    T1CLK = 0x01;       // FOSC/4
    T1CON = 0x33;       //Timer1 ON, pres 1:8
    //configuracion del CCP1
    CCP1CON = 0x81;      //CCP1 ON, modo compare clear Timer1
    CCPR1H = 0x27;
    CCPR1L = 0x10;      //Valor de referencia de comparacion 10000
    //configuracion de las interrupciones relacionadas con CCP1
    PIE3bits.CCP1IE = 1;    //habilitador de int de CCP1 ON
    INTCON0bits.GIE = 1;    //habilitado global de ints
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(19);
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
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Relojito UPCino",15);
    while(1){
        //formato de hora 24h 00:00:00:00
        POS_CURSOR(2,2);
        convierte(horas);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(':');
        convierte(minutos);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(':');
        convierte(segundos);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(':');
        convierte(centesimas);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;        //bajamos bandera CCP1IF
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

void __interrupt(irq(default)) Other_ISR(void){
    
}