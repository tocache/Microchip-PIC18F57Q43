#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

unsigned char efecto[]={0x01,0x02,0x04,0x10,0x20,0x40,0x80};

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuración de las E/S
    //configuracion del I2C
    TRISCbits.TRISC3 = 0; // outputs
    TRISCbits.TRISC4 = 0;
    ANSELCbits.ANSELC3 = 0; // digitales
    ANSELCbits.ANSELC4 = 0;
    ODCONCbits.ODCC3 = 1; // open drain
    ODCONCbits.ODCC4 = 1;
    // COnfiguracion de PPS para I2C (outputs en RC3, RC4)    
    RC3PPS = 0x37; // I2C1 SCL
    RC4PPS = 0x38; // I2C1 SDA
    // Configuracion de puerto C para i2c    
    RC3I2Cbits.PU = 2; // RC3I2C, PU = "10". 10x current of standard weak pull-up
    RC3I2Cbits.TH = 1; // RC3I2C, TH = "01". I2C-specific input thresholds
    RC4I2Cbits.PU = 2; // RC4I2C, PU = "10". 10x current of standard weak pull-up
    RC4I2Cbits.TH = 1; // RC4I2C, TH = "01". I2C-specific input thresholds    
    I2C1CON0bits.EN = 1; // habilitar modulo I2C
    I2C1CLKbits.CLK = 3; // MFINTOSC (500 kHz), lo cual genera un SCL a 100 KHz por defecto
    I2C1CON0bits.MODE = 0x4;            //I2C host mode 7bit addressing
    I2C1CON2bits.ABD = 0;               //I2C con registros independientes para Addr y Data
    //configuracion de las interrupciones
    //inicializacion del LCD
    LCD_INIT();
}

void splash_screen(void){
    POS_CURSOR(1,1);
    ESCRIBE_MENSAJE2("Prueba de I2C");
    POS_CURSOR(2,1);
    ESCRIBE_MENSAJE2("con el PCF8574");
    __delay_ms(3000);
    BORRAR_LCD();
}

void I2C1_WriteSingleByte(unsigned char direccion, unsigned char dato){
    I2C1CNT = 1;
    I2C1ADB1 = (direccion << 1) & 0xFE;     //slave addr + 0 (write)
    I2C1TXB = dato;                     //colocamos el dato a enviar
    I2C1CON0bits.S = 1; // START condition
    while(I2C1STAT1bits.TXBE == 0); // espera a que el buffer TX este vacio
    while(I2C1CON1bits.ACKSTAT == 1); // Espera a recibir la rpta del cliente (ACK))
    while(I2C1PIRbits.PCIF == 0); //Espera a terminar STOP condition
}

unsigned char I2C1_ReadSingleByte(unsigned char direccion){
    unsigned char recibido;
    I2C1CNT = 1;
    I2C1ADB1 = (direccion << 1) | 0x01;     //slave addr + 1 (read)
    I2C1CON0bits.S = 1; // START condition
    while(I2C1CON1bits.ACKSTAT == 1); // Espera a recibir la rpta del cliente (ACK))    
    recibido = I2C1RXB;
    while(I2C1STAT1bits.RXBF == 0); //espera a que el buffer de RX este lleno
    I2C1CON1bits.ACKCNT = 1;            //envio de NOACK al cliente
    while(I2C1PIRbits.PCIF == 0); //Espera a terminar STOP condition
    return recibido;
}

void main(void) {
    configuro();
    splash_screen();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("DatoDEC:");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("DatoBIN:");
    while(1){
        unsigned char x_var;
        for(x_var=0;x_var<6;x_var++){
            I2C1_WriteSingleByte(0x27, efecto[x_var]);
            POS_CURSOR(1,10);
            LCD_ESCRIBE_VAR_CHAR(efecto[x_var], 3);
            POS_CURSOR(2,9);
            LCD_VARCHAR_BITS(efecto[x_var]);
            __delay_ms(200);
        }
        for(x_var=6;x_var>0;x_var--){
            I2C1_WriteSingleByte(0x27, efecto[x_var]);
            POS_CURSOR(1,10);
            LCD_ESCRIBE_VAR_CHAR(efecto[x_var], 3);
            POS_CURSOR(2,8);
            LCD_VARCHAR_BITS(efecto[x_var]);
            __delay_ms(200);
        }
    }
}