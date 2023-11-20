#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

float kp = 6;
float ki = 0;
float kd = 0;
unsigned int setpoint = 2000;
float val_error, val_error_pasado, val_error_diferencia;
unsigned char salida_controlador = 0;
float temporal;
float PID_p=0, PID_i=0, PID_d=0, PID_total=0;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;     //HFINTOSC, posts 1:1
    OSCFRQ = 0x06;      //HFINTOSC a 32MHz
    OSCEN = 0x40;       //HFINTOSC enabled
    //configuracion del LCD
    LCD_INIT();
    //configuracion del ADC
    TRISAbits.TRISA3 = 1;       //RA0 como entrada
    ANSELAbits.ANSELA3 = 1;     //RA0 como analogica
    ADCON0bits.ADFM = 1;        //just derecha
    ADCON0bits.CS = 1;          //clock source ADCRC
    ADPCH = 0x03;               //ANA0 selected
    ADCON0bits.ON = 1;          //ADC on
    //configuracion para PWM
    RF1PPS = 0x15;  //RF1 asignado a CCP1    
    TRISFbits.TRISF1 = 0;   //RF1 salida
    ANSELFbits.ANSELF1 = 0; //RF1 digital
    T2PR = 250;             //Periodo de PWM (f=4KHz)
    CCP1CON = 0x9C;         //CCP1 enabled, PWM, left justified
    CCPR1H = 125;           //duty cycle al 50%
    CCPR1L = 0;
    T2CON = 0xA0;           //TMR2 on, 1:4 presc
    T2CLKCON = 0x01;         //TMR2 con FOSC/4
    //configuracion del Timer0 para temporizado de 50ms en interrupcion
    T0CON0 =0x90;           //modo 16 bit posts 1:1 TMR0 enabled
    T0CON1 = 0x43;          //FOSC/4 Sync 1:8 para obtener 1 us por cuenta
    PIE3bits.TMR0IE = 1;    //TMR0IE enabled
    PIR3bits.TMR0IF = 0;
    INTCON0bits.GIE = 1;    //Global interrupt enabled
}

unsigned int tomamuestra_ADC(unsigned char canal){
    uint24_t promedio = 0;
    unsigned int lectura = 0;
    unsigned int x_var;
    ADPCH = canal;
    for(x_var=0;x_var<1000;x_var++){
        ADCON0bits.GO = 1;          //inicio una toma de muestra
        while(ADCON0bits.GO == 1);  //esperar a que termine de convertir
        lectura = (ADRESH << 8) + ADRESL;
        promedio = promedio + lectura;
    }
//    temporal = lectura * 0.061;
    return promedio;
}

void splashscreen(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Controlador PID");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("Iniciando...");
    __delay_ms(3000);
    BORRAR_LCD();
}

void main(void) {
    configuro();
    while(1){
        POS_CURSOR(1,0);
        ESCRIBE_MENSAJE2("ADC CH0:");
        LCD_ESCRIBE_VAR_INT(tomamuestra_ADC(3), 4);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("PID_total:");
        LCD_ESCRIBE_VAR_INT(PID_total, 4);
    }
}

//funcion de control_PID muestrando cada 50ms por la interrupcion de desborde de Timer0
void __interrupt(irq(IRQ_TMR0)) TMR0_ISR(void){
    unsigned char x_var;
    PIR3bits.TMR0IF = 0;
    TMR0H = 0x3C;
    TMR0L = 0xB0;       //cuenta inicial 15536 para temporizar 50ms
    for(x_var=0;x_var<10;x_var++){
        temporal = ((tomamuestra_ADC(0) / 1000) * 0.061);
    }
    temporal = temporal / 10;
    val_error = setpoint - temporal;
    PID_p = kp * val_error;
    
    //val_error_diferencia = val_error - val_error_pasado;     
    PID_d = kd*((val_error - val_error_pasado)/50);
    
    //el integrador solo funciona en un rango de -100 y 100 del error
    if((-100 < val_error) && (val_error < 100)){
      PID_i = PID_i + (ki * val_error);
    }
    else{
      PID_i = 0;
    }

    PID_total = PID_p + PID_i + PID_d;  

    if (PID_total >= 250){
        PID_total = 250;
    }
    if (PID_total < 10){
        PID_total = 10;
    }
    CCPR1H = PID_total;
    val_error_pasado = val_error;
}
