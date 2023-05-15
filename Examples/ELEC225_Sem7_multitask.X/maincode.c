#include <xc.h>

void configuro(void){
    //Configuracion de la fuente de reloj principal
    OSCCON1 = 0x60;                 //HFINTOSC y Divisor en 1:1
    OSCFRQ = 0x02;                  //HFINTOSC a 4MHz
    OSCEN = 0x40;                   //HFINTOSC habilitado
    //Configuracion de las E/S
    TRISD = 0xF0;                   //RD3 al RD0 como salidas
    ANSELD = 0xF0;                  //RD3 al RD0 como digitales
    TRISFbits.TRISF0 = 0;           //RF0 como salida
    ANSELFbits.ANSELF0 = 0;         //RF0 como digital
    TRISCbits.TRISC0 = 0;           //RC0 como salida
    ANSELCbits.ANSELC0 = 0;         //RC0 como digital
    TRISBbits.TRISB0 = 1;           //RB0 como entrada
    ANSELBbits.ANSELB0 = 0;         //RB0 como digital
    WPUBbits.WPUB0 = 1;             //RB0 con weakpullup enabled
    TRISBbits.TRISB1 = 1;           //RB1 como entrada
    ANSELBbits.ANSELB1 = 0;         //RB1 como digital
    WPUBbits.WPUB1 = 1;             //RB1 con weakpullup enabled
    //Configuracion del TMR0 para temporizar 500ms
    T0CON0 = 0x90;                  //tmr0 enabled, 16bit, post 1:1
    T0CON1 = 0x53;                  //fosc/4, async, 1:8psc
    TMR0H = 0x0B;                   //cuenta inicial 3036 para temporizar 500ms
    TMR0L = 0xDC;
    //Configuracion de las interrupciones
    INTCON0bits.GIE = 1;            //interruptor global enabled
    PIE6bits.INT1IE = 1;            //INT1 habilitada
    INTCON0bits.INT1EDG = 0;        //INT1 en flanco de bajada
}

void main(void) {
    configuro();
    while(1){
        while(PIR3bits.TMR0IF == 0);
        PIR3bits.TMR0IF = 0;
        TMR0H = 0x0B;                   //cuenta inicial
        TMR0L = 0xDC;
        LATCbits.LATC0 = ~LATCbits.LATC0;
    }
}

void __interrupt() INT1_ISR(void){
    PIR6bits.INT1IF = 0;            //bajamos bandera de INT1
    LATFbits.LATF0 = ~LATFbits.LATF0;
}
