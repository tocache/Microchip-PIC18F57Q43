#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char e_acento[]={0x02,0x04,0x0E,0x11,0x1F,0x10,0x0E,0x00};
unsigned char camote = 0;
unsigned char centena, decena, unidad;
unsigned char ind = 0;

void configuro(void){
    //configuracion de la fuente de reloj del 57Q43
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //OSCCON = 0x52;        //Para el 45K50
    //configuracion de las E/S
    TRISD = 0x00;           //RD salidas
    ANSELD = 0x0;           //RD digitales
    TRISBbits.TRISB0 = 1;   //RB0 entrada
    ANSELBbits.ANSELB0 = 0; //RB0 digital
    WPUBbits.WPUB0 = 1;     //RB0 pull activado
    //INTCON2bits.RBPU = 0; //Para el 45K50
    TRISEbits.TRISE0 = 0;   //RE0 salida
    ANSELEbits.ANSELE0 = 0; //RE0 digital
    TRISAbits.TRISA0 = 1;   //RA0 entrada
    ANSELAbits.ANSELA0 = 1; //RA0 analogica
    TRISCbits.TRISC2 = 0;   //RC2 salida
    ANSELCbits.ANSELC2 = 0; //RC2 digital
}

void LCD_Init(void){
    __delay_ms(29);
    LCD_CONFIG();
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
    LATCbits.LATC2 = 1; //para activar el backlight
    GENERACARACTER(e_acento,0);
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void vis_camote(void){
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Camote:",7);
    convierte(camote);
    ENVIA_CHAR(centena+0x30);
    ENVIA_CHAR(decena+0x30);
    ENVIA_CHAR(unidad+0x30);
}

void vis_primeralinea(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Con fe aprobar",14);
    ENVIA_CHAR(0);
    ENVIA_CHAR('!');    
}

void main(void) {
    configuro();
    LCD_Init();
    vis_primeralinea();
    while(1){
        if(ind == 0){
            if(camote == 60){
                ind = 1;
            }
            else{
                camote++;
                __delay_ms(200);
            }
        }
        else{
            if(camote == 0){
                ind = 0;
            }
            else{
                camote--;
                __delay_ms(200);
            }
        }
        vis_camote();
    }
}
