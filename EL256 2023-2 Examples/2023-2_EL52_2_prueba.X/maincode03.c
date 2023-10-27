#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

unsigned int resultado = 0;     //Alojador del resultado del ADC en 12bits
unsigned int millar, centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x07;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISBbits.TRISB4 = 1;       //RB4 como entrada
    ANSELBbits.ANSELB4 = 0;     //RB4 como digital
    WPUBbits.WPUB4 = 1;         //RB4 con pullup activado
    TRISFbits.TRISF3 = 0;       //RF3 como salida
    ANSELFbits.ANSELF3 = 0;     //RF3 como digital
    //configuracion del ADC
    ADCON0bits.FM = 1;          //right justify
    ADCON0bits.CS = 1;          //ADCRC Clock
    ADPCH = 0x00;               //RA0 is Analog channel
    TRISAbits.TRISA0 = 1;       //Set RA0 to input
    ANSELAbits.ANSELA0 = 1;     //Set RA0 to analog
    ADCON0bits.ON = 1;          //Turn ADC On    
}

void lcd_init(void){
    TRISD = 0x00;       //RD salidas
    ANSELD = 0x00;      //RD digitales
    LCD_CONFIG();
    __delay_ms(19);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void convierte(unsigned int valor){
    millar = valor / 1000;
    centena = (valor % 1000) / 100;
    decena = (valor % 100) / 10;
    unidad = valor % 10;
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE("Ejerciciomon", 12);
    __delay_ms(3000);
    while(1){
        ADCON0bits.GO = 1; //Start conversion
        while(ADCON0bits.GO); //Wait for conversion done
        resultado = (ADRESH << 8) + ADRESL;
        convierte(resultado);
        POS_CURSOR(2,2);
        ESCRIBE_MENSAJE("ADC CH0:", 8);
        ENVIA_CHAR(millar+0x30);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
