#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char horas=20, minutos=23, segundos=00, centesimas=00;
unsigned centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de E/S
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 1;
    TRISBbits.TRISB1 = 1;
    ANSELBbits.ANSELB1 = 0;
    WPUBbits.WPUB1 = 1;
    //configuracion del Timer1
    T1CLK = 0x01;
    T1CON = 0x33;
    //configuracion del CCP1
    CCP1CON = 0x81;
    CCPR1H = 0x27;
    CCPR1L = 0x10;
    //configuracion de las interrupciones
    PIE3bits.CCP1IE = 1;
    PIR3bits.CCP1IF = 0;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;
    PIE6bits.INT1IE = 1;
    PIR6bits.INT1IF = 0;
    INTCON0bits.GIE = 1;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(25);
    BORRAR_LCD();
    CURSOR_ONOFF(OFF);
    CURSOR_HOME();
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
    ESCRIBE_MENSAJE("Relojon UPCino",14);
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