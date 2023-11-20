#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#include "I2C_LCD.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //inicializacion del LCD
    LCD_INIT();
    //inicializacion del I2C_LCD
    I2C_LCD_INIT();
}

void splash_screen(void){
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE2("Prueba de LCD");
    POS_CURSOR(2,1);
    ESCRIBE_MENSAJE2("Prueba de I2C");
    I2C_POS_CURSOR(1,1);
    I2C_ESCRIBE_MENSAJE2("Prueba de LCD");
    I2C_POS_CURSOR(2,1);
    I2C_ESCRIBE_MENSAJE2("Prueba de I2C");    
    __delay_ms(3000);
    BORRAR_LCD();
    I2C_BORRAR_LCD();
}

void main(void) {
    configuro();
    splash_screen();
    POS_CURSOR(1,3);
    ESCRIBE_MENSAJE2("Contador");
    I2C_POS_CURSOR(1,3);
    I2C_ESCRIBE_MENSAJE2("Contador");
    while(1){
        unsigned char x_var;
        for(x_var=0;x_var<=255;x_var++){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("DEC:");
            LCD_ESCRIBE_VAR_CHAR(x_var,3);
            POS_CURSOR(2,8);
            ESCRIBE_MENSAJE2("HEX:");
            LCD_VARCHAR_HEX(x_var);
            I2C_POS_CURSOR(2,0);
            I2C_ESCRIBE_MENSAJE2("DEC:");
            I2C_LCD_ESCRIBE_VAR_CHAR(x_var,3);
            I2C_POS_CURSOR(2,8);
            I2C_ESCRIBE_MENSAJE2("HEX:");
            I2C_LCD_VARCHAR_HEX(x_var);            
            __delay_ms(10);
            
        }
    }
}
