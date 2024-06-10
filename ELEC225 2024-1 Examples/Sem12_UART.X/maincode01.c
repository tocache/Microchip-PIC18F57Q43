#include <xc.h>
#include "cabecera.h"
#include "dht11_lib.h"
#include "LIB_UART.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
}

void splash_screen(void){
    __delay_ms(1000);
    U1_STRING_SEND("Ingenieria Electronica UPAO 2024");
    U1_NEWLINE();
    U1_STRING_SEND("Semana 12");
    U1_NEWLINE();
    U1_STRING_SEND("Taller de microcontroladores");
    U1_NEWLINE();
    __delay_ms(2000);    
}

void main(void) {
    configuro();
    U1_INIT(BAUD_9600);
    splash_screen();
    while(1){
        unsigned char RH_Ent, RH_Dec, Temp_Ent, Temp_Dec, Chksum;
        DHT11_Start();
        DHT11_Check();
        RH_Ent = DHT11_Read();
        RH_Dec = DHT11_Read();
        Temp_Ent = DHT11_Read();
        Temp_Dec = DHT11_Read();
        Chksum = DHT11_Read();  
        U1_STRING_SEND("Temperatura DHT11: ");
        U1_VAR_CHAR(Temp_Ent,2);
        U1_STRING_SEND("*C");
        U1_NEWLINE();
        U1_STRING_SEND("Humedad DHT11: ");        
        U1_VAR_CHAR(RH_Ent,2);
        U1_STRING_SEND("%RH");
        U1_NEWLINE();        
        __delay_ms(1000);
    }
}
