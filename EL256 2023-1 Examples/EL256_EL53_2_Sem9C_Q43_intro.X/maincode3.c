#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL    //frecuencia de trabajo

unsigned char e_acentuado[]={0x02,0x04,0x0E,0x11,0x1F,0x10,0x0E,0x00};
unsigned char cuenta = 0;
unsigned centena, decena, unidad;

void configuro(void){
    //configuracion del oscilador interno
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISD = 0x00;           //RD como salidas
    ANSELD = 0x00;          //RD como digitales
    TRISAbits.TRISA0 = 1;   //RA0 como entrada
    ANSELAbits.ANSELA0 = 1; //RA0 como analogica
    TRISBbits.TRISB0 = 1;   //RB0 como entrada
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup activadas
    TRISEbits.TRISE0 = 0;   //RE0 como salida
    ANSELEbits.ANSELE0 = 0; //RE0 como digital
}

void LCD_Init(void){
    __delay_ms(29);
    LCD_CONFIG();
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    LATCbits.LATC2 = 1;
    GENERACARACTER(e_acentuado, 0);
}

void splash_screen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Aprobar",7);
    ENVIA_CHAR(0);
    ESCRIBE_MENSAJE(" Micro!",7);
}

void parpadeo(void){
    __delay_ms(100);
    LATEbits.LATE0 = ~LATEbits.LATE0;
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    LCD_Init();
    splash_screen();
    while(1){
        parpadeo();
        cuenta++;
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE("Cuenta:",7);
        convierte(cuenta);
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}
