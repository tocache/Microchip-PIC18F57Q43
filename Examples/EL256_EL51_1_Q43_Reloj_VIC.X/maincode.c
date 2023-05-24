#include <xc.h>
#include <pic18f57q43.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char centena, decena, unidad;
unsigned char horas = 10, minutos = 10, segundos = 20, ticks = 0;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de los puertos
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogico
    TRISBbits.TRISB2 = 0;       //RB2 como salida
    ANSELBbits.ANSELB2 = 0;     //RB2 como digital
    //configuracion del TMR1
    T1CON = 0x01;               //TMR1 on, psc 1:1
    T1CLK = 0x01;               //TMR1 Fosc/4
    //configuracion del CCP1 en comparador evento especial de disparo
    CCP1CON = 0x8B;             //CCP1 on, compare clear TMR1
    CCPR1H = 0x27;
    CCPR1L = 0x10;              //valor de referencia de comparacion 10000    
    //configuracion de las interrupciones
    INTCON0bits.GIE = 1;        //habilitador global
    PIE3bits.CCP1IE = 1;        //habilitador del CCP1
    PIE1bits.INT0IE = 1;        //habilitador del INT0
    PIE6bits.INT1IE = 1;        //habilitador del INT1
    PIE10bits.INT2IE = 1;       //habilitador del INT2
    INTCON0bits.INT0EDG = 0;
    INTCON0bits.INT1EDG = 0;
    INTCON0bits.INT2EDG = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    //holy cow! 4 interrupt sources!
}

void lcd_config(void){
    __delay_ms(15);
    LCD_CONFIG();
    __delay_ms(15);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    LATBbits.LATB2 = 1;
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void){
    configuro();
    lcd_config();    
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("UPC 2023-1");
    __delay_ms(2000);
    BORRAR_LCD();
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE2("Relojito UPC");
    while(1){
        POS_CURSOR(2,0);
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
        convierte(ticks);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
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

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    segundos = 0;
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;
    if(ticks == 99){
        ticks = 0;
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
        ticks++;
    }
}