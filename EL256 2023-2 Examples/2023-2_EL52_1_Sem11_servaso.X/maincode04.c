#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int posicion = 2000;          //para determinar la posicion del servo

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;          //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;       //RB4 entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 digital
    WPUBbits.WPUB4 = 1;         //RB4 con pullup activado
    TRISCbits.TRISC0 = 0;       //RC0 salida
    ANSELCbits.ANSELC0 = 1;     //RC0 digital
    //configuracion del Timer0: modo 16bit, fosc/4 pres 1:8
    T0CON0 = 0x90;
    T0CON1 = 0x43;
    PIR3bits.TMR0IF = 0;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(22);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}


void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servo UPCino", 12);
    while(1){
        if(PORTBbits.RB4 == 0){
            LATCbits.LATC0 = 1;
            TMR0H = (((65535 - (posicion+500)) + 1) >> 8) & 0x00FF;
            TMR0L = ((65535 - (posicion+500)) + 1) & 0x00FF;           //cuenta inicial
            while(PIR3bits.TMR0IF == 0);
            PIR3bits.TMR0IF = 0;
            LATCbits.LATC0 = 0;
            TMR0H = (48036 >> 8) & 0x00FF;
            TMR0L = 48036 & 0x00FF;           //cuenta inicial
            
            //(65535 - (posicion+500)) + 1)       //TON
            //45536 + (65535 - (posicion+500)) + 1)        
            
            while(PIR3bits.TMR0IF == 0);
            PIR3bits.TMR0IF = 0;
        }
        else{
            LATCbits.LATC0 = 1;
            TMR0H = (65036 >> 8) & 0x00FF;
            TMR0L = 65036 & 0x00FF;           //cuenta inicial
            while(PIR3bits.TMR0IF == 0);
            PIR3bits.TMR0IF = 0;
            LATCbits.LATC0 = 0;
            TMR0H = (46036 >> 8) & 0x00FF;
            TMR0L = 46036 & 0x00FF;           //cuenta inicial
            while(PIR3bits.TMR0IF == 0);
            PIR3bits.TMR0IF = 0;
        }
    }
}