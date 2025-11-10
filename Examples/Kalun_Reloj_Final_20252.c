//Reloj con alarma
//Hecho por Kalun Lau
//UPC 07 de Noviembre del 2025

#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL
#define RELOJ 0
#define SET_CLK 1
#define SET_AL 2
#define APAGADA 3
#define ENCENDIDA 4

unsigned char horas=10,minutos=10,segundos=10,centesimas=10;	//hora inicial 10:10'10"10
unsigned char al_hora=17,al_mins=00;	//alarma ajustada a 17:00 inicialmente
unsigned char centena,decena,unidad;
unsigned char MODO = RELOJ;
unsigned char ALARM = APAGADA;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC, posts 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion de E/S
    TRISB = 0xFF;       //RB2 RB1 RB0 como entradas
    ANSELB = 0xF8;      //RB2 RB1 RB0 como digitales
    WPUB = 0x07;        //RB2 RB1 RB0 pullup enabled
    TRISEbits.TRISE0 = 0;
    ANSELEbits.ANSELE0 = 0;    //RE0 estara el buzzer
    //configuracion del Timer1
    T1CLK = 0x01;       //clk source fosc/4
    T1CON = 0x33;       //TMR1 ON, pres 1:8
    //configuracion del CCP1
    CCP1CON = 0x81;     //compare mode, clear TMR1
    CCPR1H = 0x27;
    CCPR1L = 0x10;      //valor de referencia 10000
    //configuracion de las interrupciones
    INTCON0bits.INT0EDG = 0;    //falling edge en INT0
    INTCON0bits.INT1EDG = 0;    //falling edge en INT1
    INTCON0bits.INT2EDG = 0;    //falling edge en INT2
    PIE1bits.INT0IE = 1;        //INT0 enabled
    PIE6bits.INT1IE = 1;        //INT1 enabled
    PIE10bits.INT2IE = 1;	//INT2 enabled
    PIE3bits.CCP1IE = 1;        //CCP1 enabled
    PIR1bits.INT0IF = 0;        //flag INT0 bajada
    PIR6bits.INT1IF = 0;        //flag INT2 bajada
    PIR10bits.INT2IF = 0;	//flag INT2 bajo
    PIR3bits.CCP1IF = 0;        //flag CCP1 bajada
    INTCON0bits.GIE = 1;        //global ints enabled
    //condiciones iniciales
    LATEbits.LATE0 = 0;		//buzzer apagado
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

void convierte(unsigned char numero){
    centena = numero / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void DISP_ALARMA(void){
    POS_CURSOR(1,14);
    ESCRIBE_MENSAJE("AL",2);
    POS_CURSOR(2,14);
    if(ALARM == APAGADA){
        ESCRIBE_MENSAJE("OF",2);
    }
    else if(ALARM == ENCENDIDA){
        ESCRIBE_MENSAJE("ON",2);
    }
}

void CTL_AL(void){
    if(al_hora == horas && al_mins == minutos && ALARM == ENCENDIDA){
	LATEbits.LATE0 = 1;	//suena el buzzer
    }
    else{
	LATEbits.LATE0 = 0;	//buzzer apagado
    }
}

void main(void) {
    configuro();
    lcd_init();
    while(1){
        switch(MODO){
    	    case RELOJ:
    		POS_CURSOR(1,2);
    		ESCRIBE_MENSAJE("Relojon UPC",11);
    	        POS_CURSOR(2,2);
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
    	        convierte(centesimas);
    	        ENVIA_CHAR(decena+0x30);
            	ENVIA_CHAR(unidad+0x30);
                DISP_ALARMA();
                CTL_AL();
                break;
            case SET_CLK:
                POS_CURSOR(1,2);
                ESCRIBE_MENSAJE("Set Clock  ",11);
                POS_CURSOR(2,2);
                convierte(horas);
                ENVIA_CHAR(decena+0x30);
                ENVIA_CHAR(unidad+0x30);
                ENVIA_CHAR(':');
                convierte(minutos);
                ENVIA_CHAR(decena+0x30);
                ENVIA_CHAR(unidad+0x30);
                ESCRIBE_MENSAJE("      ",6);
                DISP_ALARMA();
                break;
            case SET_AL:
                POS_CURSOR(1,2);
                ESCRIBE_MENSAJE("Set Alarm  ",11);
                POS_CURSOR(2,2);
                convierte(al_hora);
                ENVIA_CHAR(decena+0x30);
                ENVIA_CHAR(unidad+0x30);
                ENVIA_CHAR(':');
                convierte(al_mins);
                ENVIA_CHAR(decena+0x30);
                ENVIA_CHAR(unidad+0x30);
                ESCRIBE_MENSAJE("      ",6);
                DISP_ALARMA();
                break;
        }
    }      
}

void __interrupt(irq(IRQ_CCP1)) CCP1_ISR(void){
    PIR3bits.CCP1IF = 0;
    if(centesimas == 99){
        centesimas = 0;
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
        centesimas++;
    }
}

//cambio de modo
void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    PIR1bits.INT0IF = 0;
    switch(MODO){
	case RELOJ:
	    MODO = SET_CLK;
	    break;
	case SET_CLK:
	    MODO = SET_AL;
	    break;
	case SET_AL:
	    MODO = RELOJ;
	    break;
	}
}

void __interrupt(irq(IRQ_INT1)) INT1_ISR(void){
    PIR6bits.INT1IF = 0;
    switch(MODO){
	case RELOJ:
	    ALARM = ENCENDIDA;
	    break;
	case SET_CLK:
	    if(horas == 23){
        	horas = 0;
	    }
	    else{
        	horas++;
	    }
	    break;
	case SET_AL:
	    if(al_hora == 23){
        	al_hora = 0;
	    }
	    else{
        	al_hora++;
	    }
	    break;
    }
}

void __interrupt(irq(IRQ_INT2)) INT2_ISR(void){
    PIR10bits.INT2IF = 0;
    switch(MODO){
	case RELOJ:
	    ALARM = APAGADA;
	    break;
	case SET_CLK:
	    if(minutos == 59){
        	minutos = 0;
	    }
	    else{
	        minutos++;
	    }
	    break;
	case SET_AL:
	    if(al_mins == 59){
        	al_mins = 0;
	    }
	    else{
        	al_mins++;
	    }
	    break;
	}
}

void __interrupt(irq(default)) DEFAULT_ISR(void)
{
// Unhandled interrupts go here
}