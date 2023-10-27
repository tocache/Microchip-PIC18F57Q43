#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 48000000UL

void configuro(void){
    //configuracion de la fuente de reloj
    OSCCON1 = 0x60;     //HFINTOSC, POSTS 1:1
    OSCFRQ = 0x07;      //HFINTOSC a 48MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de las E/S
    TRISBbits.TRISB4 = 1;   //RB4 como entrada
    ANSELBbits.ANSELB4 = 0; //RB4 como digital
    WPUBbits.WPUB4 = 1;     //RB4 pullup enabled
    TRISBbits.TRISB0 = 0;   //RB0 como salida
    ANSELBbits.ANSELB0 = 0; //RB0 como digital    
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

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("El parpadeador",14);
    while(1){
        if(PORTBbits.RB4 == 0){
            //Verdadero
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Modo: epileptico",16);
            LATBbits.LATB0 = 1;
            __delay_ms(50);
            LATBbits.LATB0 = 0;
            __delay_ms(50);
        }
        else{
            //Falso
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Modo: tortuga   ",16);
            LATBbits.LATB0 = 1;
            __delay_ms(200);
            LATBbits.LATB0 = 0;
            __delay_ms(200);
        }        
    }
}
