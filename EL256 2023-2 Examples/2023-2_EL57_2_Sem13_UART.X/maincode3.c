#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned int lectura_ADC = 0;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;         //HFINTOSC div 1:1
    OSCFRQ = 0x06;          //HFINTOSC a 32MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    //configuracion de las E/S
    TRISAbits.TRISA0 = 1;   //RA0 como entrada
    ANSELAbits.ANSELA0 = 1; //RA0 como analogico
    TRISBbits.TRISB0 = 1;   //RB0 como entrada
    ANSELBbits.ANSELB0 = 0; //RB0 como digital
    WPUBbits.WPUB0 = 1;     //RB0 pullup activada
    TRISBbits.TRISB1 = 1;   //RB1 como entrada
    ANSELBbits.ANSELB1 = 0; //RB1 como digital
    WPUBbits.WPUB1 = 1;     //RB1 pullup activada
    TRISCbits.TRISC0 = 0;   //RC0 como salida
    ANSELCbits.ANSELC0 = 0; //RC0 como digital
    TRISCbits.TRISC1 = 0;   //RC1 como salida
    ANSELCbits.ANSELC1 = 0; //RC1 como digital
    TRISFbits.TRISF0 = 0;   //RF0 como salida
    ANSELFbits.ANSELF0 = 0; //RF0 como digital
    TRISFbits.TRISF1 = 1;   //RF1 como entrada
    ANSELFbits.ANSELF1 = 0; //RF1 como digital
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On      
    //configuracion del UART1
    U1BRGH = 0;
    U1BRGL = 207;           //9600 baudios
    U1CON0 = 0x20;          //BRGS=0, TX enabled
    U1CON1 = 0x80;          //UART1 ON
    U1CON2 = 0x00;          //valores por defecto
    RF0PPS = 0x20;          //RF0 conectado al TX del UART1
    //inicializacion del LCD
    LCD_INIT();
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void U1_STRING_SEND(const char *cadena){
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
}

void U1_NEW_LINE(void){
    U1_BYTE_SEND(10);
    U1_BYTE_SEND(13);
}

unsigned int tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH << 8) + ADRESL;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola Semana 13");
    U1_STRING_SEND("Arrancando sistema");
    U1_NEW_LINE();
    __delay_ms(3000);
    U1_STRING_SEND("Sistema arrancado!");
    U1_NEW_LINE();
    __delay_ms(3000);    
    while(1){
        lectura_ADC = tomamuestra_ADC();
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("Canal ANA0:");
        LCD_ESCRIBE_VAR_INT(lectura_ADC, 5);
        if(lectura_ADC >= 0 && lectura_ADC < 400){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("    Verde");
            U1_STRING_SEND("Color Verde");
            U1_NEW_LINE();
        }
        else if(lectura_ADC >= 400 && lectura_ADC < 800){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2(" Amarillo");
            U1_STRING_SEND("Color Amarillo");
            U1_NEW_LINE();
        }
        else if(lectura_ADC >= 800 && lectura_ADC < 1200){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("     Azul");
            U1_STRING_SEND("Color Azul");
            U1_NEW_LINE();
        }
        else if(lectura_ADC >= 1200 && lectura_ADC < 1600){
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("     Rojo");
            U1_STRING_SEND("Color Rojo");
            U1_NEW_LINE();
        }
        else{
            POS_CURSOR(2,0);
            ESCRIBE_MENSAJE2("    Negro");
            U1_STRING_SEND("Color Negro");
            U1_NEW_LINE();
        }
    }
}
