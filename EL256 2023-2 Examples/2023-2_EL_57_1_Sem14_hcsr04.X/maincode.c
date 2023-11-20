#include <xc.h>
#include "cabecera.h"
#include "LCD.h"

#define _XTAL_FREQ 32000000UL
#define DISPARO             1
#define ESPERA_FLANCO_SUB   2
#define ESPERA_FLANCO_BAJ   3
#define CALCULAR            4
#define MOSTRAR_DISTANCIA   5

unsigned char estado = 0;
float tiempo = 0.00;
unsigned int distancia = 0;

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;              //HFINTOSC a 32MHz
    OSCEN = 0x40;
    //configuracion de las E/S
    TRISAbits.TRISA0 = 0;       //salida
    ANSELAbits.ANSELA0 = 0;     //digital
    LATAbits.LATA0 = 0;         //valor inicial cero
    TRISCbits.TRISC2 = 1;       //entrada
    ANSELCbits.ANSELC2 = 0;     //digital
    CCP1CONbits.EN = 1;         //encendemos el CCP1
    CCP1CONbits.MODE = 5;     //Entrada CAPTURA FLANCO SUB.
    T1CLK = 0x01;       //Timer1 con fuente de reloj FOSC/4
    T1CON = 0x33;       //presc 1:8, rd16=1, async, timer1 ON
    //configuracion de las interrupciones
    INTCON0bits.GIE = 1;
    PIE3bits.CCP1IE=1;
    LCD_INIT();                 //inicializacion del LCD
}

void splash_screen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Ultrasonido");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("con HC-SR04");
    __delay_ms(3000);
    BORRAR_LCD();
    estado = DISPARO;
}

void main(void){
    configuro();
    splash_screen();
    while(1){
        switch(estado){
            case DISPARO:
                LATAbits.LATA0=1;
                __delay_us(10);
                LATAbits.LATA0=0;
                estado=ESPERA_FLANCO_SUB;
                break;
            case CALCULAR:
                tiempo=(float)distancia;
                tiempo=tiempo / 5.8;
                distancia = (int)tiempo + 1;
                estado = MOSTRAR_DISTANCIA;
                break;
            case MOSTRAR_DISTANCIA:
                POS_CURSOR(1,0);
                ESCRIBE_MENSAJE2("Midiendo...");
                POS_CURSOR(2,0);
                LCD_ESCRIBE_VAR_INT(distancia, 4, 1);
                ESCRIBE_MENSAJE2(" cm");
                __delay_ms(200);
                estado = DISPARO;
                break;
        }
    }
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    char dato=0;
    if(PIR3bits.CCP1IF==1)
    {
        PIR3bits.CCP1IF=0;
        switch(estado)
        {
            case ESPERA_FLANCO_SUB:
                TMR1H=0;
                TMR1L=0;
                CCP1CONbits.MODE = 4;
                estado = ESPERA_FLANCO_BAJ;
                break;
            case ESPERA_FLANCO_BAJ:
                distancia=CCPR1;
                estado = CALCULAR;
                CCP1CONbits.MODE = 5;
                break;
        }
    }
}

void __interrupt(irq(default)) DEFAULT_ISR(void)
{
    return;
}