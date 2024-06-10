//#include <pic18f57q43.h>

#include "dht11_lib.h"

void DHT11_Start(void){
    TRISBbits.TRISB0 = 0;      //Puerto RB0 como salida
    ANSELBbits.ANSELB0 = 0;
    LATBbits.LATB0 = 0;       //Mandamos cero
    __delay_ms(18);         //Esperamos 18 milisegundo
    LATBbits.LATB0 = 1;       //Mandamos uno
    __delay_us(40);         //Esperamos 40 microsegundos
    TRISBbits.TRISB0 = 1;      //Puerto como entrada
}

void DHT11_Check(void){
    while(PORTBbits.RB0);
    __delay_us(80);
    while(!PORTBbits.RB0);
    __delay_us(80);
    while(PORTBbits.RB0);
}

unsigned char DHT11_Read(void){
    unsigned char x = 0, data = 0;
    for(x=0;x<8;x++){
        while(!PORTBbits.RB0);
        __delay_us(35);
        if(PORTBbits.RB0){
            data = ((data<<1) | 1);
        }
        else{
            data = (data<<1);
        }
        while(PORTBbits.RB0);
    }
    return data;
}