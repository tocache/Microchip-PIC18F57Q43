#include <xc.h>
#include <pic18f57q43.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char centena, decena, unidad;
unsigned char horas = 10, minutos = 10, segundos = 20, ticks = 0;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x02;
    OSCEN = 0x40;
    //configuracion de los puertos
    TRISD = 0x00;
    ANSELD = 0x00;
    TRISAbits.TRISA0 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA0 = 1;     //RA0 como analogico
    TRISB = 0xFF;               //RB2 a RB0 como entradas
    ANSELB = 0xF8;              //RB2 a RB0 como digital
    WPUB = 0x07;                //RB2 a RB0 con pullups habilitados
    TRISCbits.TRISC2 = 0;
    ANSELCbits.ANSELC2 = 1;    
    //configuracion del ADC
    ADCON0bits.ADFM = 0;        //justificacion a la izquierda
    ADCON0bits.CS = 1;          //fuente de reloj ADCRC
    ADPCH = 0x00;               //canal analógico RA0
    ADCON0bits.ADON = 1;        //ADC On    
    //configuracion del CCP2 para PWM
    T2PR = 62;               //frecuencia de PWM a 1KHz
    RC2PPS = 0x15;          //PPS asignación de RC2 hacia CCP1
    CCP2CON = 0x9C;         //CCP1 ON, justificacion izquierda, PWM mode
    CCPR2H = 0;
    CCPR2L = 0;             //duty cycle a 0%
    T2CLKCON = 0x01;        //Timer2 Fosc/4
    T2CON = 0xC0;           //Timer2 ON psc 1:16    
    //configuracion del TMR1
    T1CON = 0x01;               //TMR1 on, psc 1:1
    T1CLK = 0x01;               //TMR1 Fosc/4
    //configuracion del CCP1 en comparador evento especial de disparo
    CCP1CON = 0x8B;             //CCP1 on, compare clear TMR1
    CCPR1H = 0x27;
    CCPR1L = 0x10;              //valor de referencia de comparacion 10000    
    //configuracion de las interrupciones
    INTCON0bits.GIE = 1;        //habilitador global
    PIE3bits.CCP1IE = 1;        //habilitador del CCP1
    PIE1bits.INT0IE = 1;        //habilitador del INT0
    PIE6bits.INT1IE = 1;        //habilitador del INT1
    PIE10bits.INT2IE = 1;       //habilitador del INT2
    INTCON0bits.INT0EDG = 0;    //INT0 en flanco de bajada
    INTCON0bits.INT1EDG = 0;    //INT1 en flanco de bajada
    INTCON0bits.INT2EDG = 0;    //INT2 en flanco de bajada
    //holy cow! 4 interrupt sources!
}

void lcd_config(void){
    __delay_ms(15);
    LCD_CONFIG();
    __delay_ms(15);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
}

void main(void){
    configuro();
    lcd_config();    
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Hola mundo");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("UPC 2023-1");
    __delay_ms(2000);
    BORRAR_LCD();
    POS_CURSOR(1,2);
    ESCRIBE_MENSAJE2("Relojito UPC");
    while(1){
        tomamuestra_ADC();
        CCPR2L = ADRESH;
        POS_CURSOR(2,0);
        convierte(horas);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(':');
        convierte(minutos);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(':');
        convierte(segundos);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(':');
        convierte(ticks);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
    }
}

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    if(horas == 23){
        horas = 0;
    }
    else{
        horas++;
    }
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    if(minutos == 59){
        minutos = 0;
    }
    else{
        minutos++;
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    segundos = 0;
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;
    if(ticks == 99){
        ticks = 0;
        if(segundos == 59){
            segundos = 0;
            if(minutos == 59){
                minutos = 0;
                if(horas == 23){
                    horas = 0;
                }
                else{
                    horas++;
                }
            }
            else{
                minutos++;
            }
        }
        else{
            segundos++;
        }
    }
    else{
        ticks++;
    }
}

void __interrupt(irq(default)) Other_ISR(void){
    
}
