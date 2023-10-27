#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char diez_millar,millar,centena,decena, unidad;
//unsigned int posicion = 1000;         //valor entre 0 (0 grados) y 2000 (180 grados)
//unsigned int cuenta_TON_0deg = 65036;          //0 grados
//como TOF = T-TON
//unsigned int cuenta_TOF_0deg = 45536 + (65535 - cuenta_TON_0deg) + 1;
//unsigned int cuenta_TON_180deg = 63036;            //180 grados
//como TOF = T-TON
//unsigned int cuenta_TOF_180deg = 45536 + (65535 - cuenta_TON_180deg) + 1;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;  //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 entrada
    ANSELBbits.ANSELB4 = 0; //RB4 digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0;  //RC0 digital
    //configuracion de Timer0 Fosc/4, modo 16bit, pres 1:8
    T0CON0 = 0x90;
    T0CON1 = 0x53;
    PIR3bits.TMR0IF = 0;
    PIE3bits.TMR0IE = 1;
    INTCON0bits.GIE = 1;
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(25);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

unsigned int escalamiento(unsigned int numero){
    unsigned int temporal1;
    temporal1 = 65036 - numero;
    return temporal1;
}

void convierte(unsigned int numero){
    diez_millar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servomon UPC",12);
    POS_CURSOR(2,0);
    while(1){
        if(PORTBbits.RB4 == 0){
            unsigned int x;
            for(x=500;x<=1500;x+=10){
                posicion = x;
                convierte(posicion);
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE("Posicion:",9);
                ENVIA_CHAR(millar+0x30);
                ENVIA_CHAR(centena+0x30);
                ENVIA_CHAR(decena+0x30);
                ENVIA_CHAR(unidad+0x30);
            }
            for(x=1500;x>500;x-=10){
                posicion = x;
                convierte(posicion);
                POS_CURSOR(2,0);
                ESCRIBE_MENSAJE("Posicion:",9);
                ENVIA_CHAR(millar+0x30);
                ENVIA_CHAR(centena+0x30);
                ENVIA_CHAR(decena+0x30);
                ENVIA_CHAR(unidad+0x30);
            }
        }
        else{
            posicion = 0;
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Posicion:0000",13);
        }
    }
}
//la precarga de la cuenta inicial se debe de hacer por separado, TMR0H primero
//y luego TMR0L luego.
void __interrupt(irq(IRQ_TMR0)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0;
    if(PORTCbits.RC0 == 0){
        LATCbits.LATC0 = 1;
        TMR0H = (escalamiento(posicion) >> 8) & 0x00FF;
        TMR0L = escalamiento(posicion) & 0x00FF;
    }
    else{
        LATCbits.LATC0 = 0;
        TMR0H = ((45536 + (65535 - escalamiento(posicion)) + 1) >> 8) & 0x00FF;
        TMR0L = (45536 + (65535 - escalamiento(posicion)) + 1) & 0x00FF;
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void){
// Unhandled interrupts go here
}
