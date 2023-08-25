#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define XTAL_FREQ 4000000UL

unsigned char diezmillar, millar, centena, decena, unidad;
unsigned char nivel = 0;

void configuro(void){
    //configuracion de reloj
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de E/S
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSELB0 = 0;
    WPUBbits.WPUB0 = 0;
    TRISFbits.TRISF0 = 0;
    ANSELFbits.ANSELF0 = 0;
    TRISFbits.TRISF1 = 1;
    ANSELFbits.ANSELF1 = 0;
    TRISD = 0x00;
    ANSELD = 0x00;
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x00;           //canal analógico RA0
    ADCON0bits.ADON = 1;      //ADC On
    ADREF = 0x03;           //Vref+ conectado a FVR_buf1
    FVRCON = 0x81;          //modulo FVR entregando 1.024V a FVR_buf1
    //configuracion del CCP1 para que entregue PWM al contraste del LCD
    T2PR = 62;               //frecuencia de PWM a 1KHz
    RC2PPS = 0x15;          //PPS asignación de RC2 hacia CCP1
    CCP1CON = 0x9C;         //CCP1 ON, justificacion izquierda, PWM mode
    CCPR1H = 19;
    CCPR1L = 0;             //duty cycle a 50%
    T2CLKCON = 0x01;        //Timer2 Fosc/4
    T2CON = 0xC0;           //Timer2 ON psc 1:16
    //configuracion de las interrupciones
    INTCON0bits.GIE = 1;
    PIE1bits.INT0IE = 1;
    INTCON0bits.INT0EDG = 0;
    //configuración del UART
    U1BRGH = 0x00;
    U1BRGL = 25;      //BRG=25 para 9600 baudios con BRGS=0
    //U3BRGS = 0;         //normal speed
    U1CON0 = 0x30;      //BRGS=0, TXEN=1, RXEN=0, MODE=00 (8bit async uart)
    RF0PPS = 0x20;       //asignación de RF0 para TX de UART1 
    U1CON1 = 0x80;      // UART1 enabled
    U1CON2 = 0x00;      //por seacaso
    //configuracion inicial del LCD
    LCD_INIT();
}


void UART1_Data_Send(unsigned char dato){
    U1TXB = dato;
    while(U3ERRIRbits.TXMTIF == 0);
}

void UART1_String_Send(const char *cadena)
{
	unsigned char tam2;
    unsigned char i = 0;
    tam2 = strlen(cadena);
	for(i = 0; i<tam2; i++)
	{
        U1TXB = cadena[i];
        while(U1ERRIRbits.TXMTIF == 0);
	}
}    

void convierte(unsigned int numero){
    diezmillar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

unsigned int tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH << 8) + ADRESL;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Primer ejemplo");
    while(1){
        convierte(tomamuestra_ADC()/40);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("LM35:");
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(0xDF);
        ENVIA_CHAR('C');
        UART1_String_Send("LM35:");
        UART1_Data_Send(decena+0x30);
        UART1_Data_Send(unidad+0x30);
        UART1_Data_Send('C');
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    switch(nivel){
        case 0:
            CCPR1H = 5;
            nivel = 1;
            break;
        case 1:
            CCPR1H = 15;
            nivel = 2;
            break;
        case 2:
            CCPR1H = 25;
            nivel = 3;
            break;
        case 3:
            CCPR1H = 35;
            nivel = 4;
            break;
        case 4:
            CCPR1H = 45;
            nivel = 5;
            break;
        case 5:
            CCPR1H = 55;
            nivel = 6;
            break;
        case 6:
            CCPR1H = 62;
            nivel = 0;
            break;
    }
}
