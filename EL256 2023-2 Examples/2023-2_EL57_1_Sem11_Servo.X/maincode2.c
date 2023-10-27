#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int Timer0_16 = 45536;     //cuenta inicial
unsigned int Timer0_OF = 46536;     //cuenta para 0 grados
//unsigned int Timer0_OF = 47536;     //cuenta para 180 grados
unsigned int Timer0_actual = 0;     //cuenta actual del timer0
unsigned char diez_millar, millar, centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;        //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S de la aplicacion
    TRISCbits.TRISC0 = 0;   //RC0 salida
    ANSELCbits.ANSELC0 = 0; //RC0 digital
    //configuración del Timer0
    T0CON0 = 0x90;      //Timer0 Enabled, 16 bit mode
    T0CON1 = 0x53;      //Fosc/4, async, 1:8 pre
    TMR0H = (Timer0_16 >> 8) & 0x00FF;
    TMR0L = (Timer0_16 & 0x00FF);       //carga de cuenta inicial
    PIR3bits.TMR0IF = 0;        //forzar la bandera de TMR0 a cero
}

void lcd_init(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    LCD_CONFIG();
    __delay_ms(23);
    BORRAR_LCD();
    CURSOR_ONOFF(OFF);
    CURSOR_HOME();
}

convierte(unsigned int numero){
    diez_millar = numero / 10000;
    millar = (numero % 10000 ) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servo prueba",12);
    while(1){
        unsigned int x;
        for(x=0;x<1000;x++){
            LATCbits.LATC0 = 1;
            TMR0H = (Timer0_16 >> 8) & 0x00FF;
            TMR0L = (Timer0_16 & 0x00FF);       //carga de cuenta inicial
            while(((TMR0H << 8) + TMR0L) != Timer0_OF);
            LATCbits.LATC0 = 0;
            while(PIR3bits.TMR0IF == 0);
            PIR3bits.TMR0IF = 0;            
        }
    }
}        
        
//        while(PIR3bits.TMR0IF == 0){
//            while(Timer0_actual != Timer0_OF);
//            LATCbits.LATC0 = 0;
//        }
//        Timer0_actual = (TMR0H << 8) + TMR0L;
//        POS_CURSOR(2,0);
//        ESCRIBE_MENSAJE("TMR0:", 5);
//        convierte(Timer0_actual);
//        ENVIA_CHAR(diez_millar+0x30);
//        ENVIA_CHAR(millar+0x30);
//        ENVIA_CHAR(centena+0x30);
//        ENVIA_CHAR(decena+0x30);
//        ENVIA_CHAR(unidad+0x30);        
//        PIR3bits.TMR0IF = 0;

