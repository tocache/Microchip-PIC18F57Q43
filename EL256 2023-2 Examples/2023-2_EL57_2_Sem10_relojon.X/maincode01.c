#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char horas=20,minutos=02,segundos=16,centesimas=58;
unsigned char centena,decena,unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion del Timer1
    T1CLK = 0x01;
    T1CON = 0x33;
    //configuracion del CCP1
    CCP1CON = 0x81;
    CCPR1H = 0x27;
    CCPR1L = 0x10;
    //configuracion de las interrupciones
    PIE3bits.CCP1IE = 1;
    INTCON0bits.GIE = 1;
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
