#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char horas=10,minutos=10,segundos=10,centesimas=10;
unsigned char centena,decena,unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC, posts 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de E/S
    TRISB = 0xFF;       //RB1 RB0 como entradas
    ANSELB = 0xFC;      //RB1 RB0 como digitales
    WPUB = 0x03;        //RB1 RB0 pullup enabled
    //configuracion del Timer1
    T1CLK = 0x01;       //clk source fosc/4
    T1CON = 0x33;       //TMR1 ON, pres 1:8
    //configuracion del CCP1
    CCP1CON = 0x81;     //compare mode, clear TMR1
    CCPR1H = 0x27;
    CCPR1L = 0x10;      //valor de referencia 10000
    //configuracion de las interrupciones
    INTCON0bits.INT0EDG = 0;    //falling edge en INT0
    INTCON0bits.INT1EDG = 0;    //falling edge en INT1
    PIE1bits.INT0IE = 1;        //INT0 enabled
    PIE6bits.INT1IE = 1;        //INT1 enabled
    PIE3bits.CCP1IE = 1;        //CCP1 enabled
    PIR1bits.INT0IF = 0;        //flag INT0 bajada
    PIR6bits.INT1IF = 0;        //flag INT2 bajada
    PIR3bits.CCP1IF = 0;        //flag CCP1 bajada
    INTCON0bits.GIE = 1;        //global ints enabled
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(21);
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
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Relojon UPC",11);
    while(1){
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

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(horas == 23){
        horas = 0;
    }
    else{
        horas++;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(minutos == 59){
        minutos = 0;
    }
    else{
        minutos++;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void)
{
// Unhandled interrupts go here
}