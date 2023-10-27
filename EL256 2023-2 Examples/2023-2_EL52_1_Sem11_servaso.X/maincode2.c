#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

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

void servo_45(void){
    unsigned int x_var;
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Servo a 045", 11);
    ENVIA_CHAR(0xDF);
    for(x_var=0;x_var<=20;++x_var){
        LATCbits.LATC0 = 1; //mover al medio 45°
        __delay_us(1000);
        LATCbits.LATC0 = 0;
        __delay_us(19000);
    }    
}

void servo_90(void){
    unsigned int x_var;
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Servo a 090", 11);
    ENVIA_CHAR(0xDF);
    for(x_var=0;x_var<=20;++x_var){
        LATCbits.LATC0 = 1; 
        __delay_us(1500);
        LATCbits.LATC0 = 0;
        __delay_us(18500);
    }    
}

void servo_135(void){
    unsigned int x_var;
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Servo a 135", 11);
    ENVIA_CHAR(0xDF);
    for(x_var=0;x_var<=20;++x_var){
        LATCbits.LATC0 = 1;
        __delay_us(2000);
        LATCbits.LATC0 = 0;
        __delay_us(18000);
    }    
}

void servo_180(void){
    unsigned int x_var;
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Servo a 180", 11);
    ENVIA_CHAR(0xDF);
    for(x_var=0;x_var<=20;++x_var){
        LATCbits.LATC0 = 1;
        __delay_us(2500);
        LATCbits.LATC0 = 0;
        __delay_us(17500);
    }    
}

void servo_0(void){
    unsigned int x_var;
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE("Servo a 000", 11);
    ENVIA_CHAR(0xDF);
    for(x_var=0;x_var<=20;++x_var){
        LATCbits.LATC0 = 1; 
        __delay_us(500);
        LATCbits.LATC0 = 0;
        __delay_us(19500);
    }    
}

void main(void) {
    configuro();
    lcd_init();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE("Servo UPCino", 12);
    while(1){
        if(PORTBbits.RB4 == 0){
            servo_45();
            servo_90();
            servo_135();
            servo_180();
            servo_135();
            servo_90();
            servo_45();
            servo_135();
            servo_90();
            servo_180();
            servo_45();
        }
        else{
            LATCbits.LATC0 = 1;
            __delay_us(500);
            LATCbits.LATC0 = 0;
            __delay_us(19500);
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE("Servo a 000", 11);
            ENVIA_CHAR(0xDF);
        }
    }
}
