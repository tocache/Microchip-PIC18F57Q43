#include <xc.h>
#include <string.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 32000000UL

int16_t const_offset, const_gain;

void configuro(void){
    //configuracion del oscilador
    OSCCON1 = 0x60;         //HFINTOSC div 1:1
    OSCFRQ = 0x06;          //HFINTOSC a 32MHz
    OSCEN = 0x40;           //HFINTOSC enabled
    //configuracion del ADC
    ADCON0bits.ADFM = 1;    //justificacion a la derecha
    ADCON0bits.CS = 1;      //fuente de reloj ADCRC
    ADPCH = 0x3C;           //canal analógico RA0
    ADREF = 0x03;           //PREF conectado a FVR
    FVRCON = 0xB2;          //FVR enabled, Tempind enabled highrange, FVR Buffer1 en 2.048V
    ADCON0bits.ADON = 1;      //ADC On      
    //inicializacion del LCD
    LCD_INIT();
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

unsigned int tomamuestra_ADC(unsigned char canal){
    ADPCH = canal;           //canal analógico
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH << 8) + ADRESL;
}

void get_DIA_values(void){
    unsigned char TSHR1H, TSHR1L, TSHR3H, TSHR3L;
    TBLPTRU = 0x2C;
    TBLPTRH = 0x00;
    TBLPTRL = 0x2A;     //apuntando a TSLR1 del DIA
    asm("TBLRD*+");
    TSHR1L = TABLAT;
    asm("TBLRD*"); 
    TSHR1H = TABLAT;    
    const_gain = ((TSHR1H << 8) + TSHR1L);
    TBLPTRU = 0x2C;
    TBLPTRH = 0x00;
    TBLPTRL = 0x2E;     //apuntando a TSHR1 del DIA
    asm("TBLRD*+");
    TSHR3L = TABLAT;
    asm("TBLRD*"); 
    TSHR3H = TABLAT;    
    const_offset = ((TSHR3H << 8) + TSHR3L);
}

/*funcion de prueba para visualizar valores de TSLR1 y TSLR3 en binario en el LCD
void show_TSLR1_TSLR3_values(void){
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("TSLR1H:");
    LCD_VARCHAR_BITS(TSLR1H);
    __delay_ms(3000);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("TSLR1L:");
    LCD_VARCHAR_BITS(TSLR1L);
    __delay_ms(3000);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("TSLR3H:");
    LCD_VARCHAR_BITS(TSLR3H);
    __delay_ms(3000);
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("TSLR3L:");
    LCD_VARCHAR_BITS(TSLR3L);
    __delay_ms(3000);
}*/

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("Temp. Indicator");
    get_DIA_values();
    while(1){
        unsigned int lectura_ADC;
        int24_t temporal;
/*        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("G:");
        LCD_ESCRIBE_VAR_INT(const_gain,5);
        ESCRIBE_MENSAJE2(" O:");
        LCD_ESCRIBE_VAR_INT(const_offset,5);
        __delay_ms(3000);*/
        
        lectura_ADC = tomamuestra_ADC(0x3C);
        temporal = (int24_t)(lectura_ADC) * const_gain;
        temporal = temporal / 256;
        temporal = temporal + const_offset;
        temporal = temporal / 10;
        
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("Value: ");
        LCD_ESCRIBE_VAR_INT(temporal,5);        
        LCD_CHAR_GRADO();
        ESCRIBE_MENSAJE2("C   ");
        __delay_ms(100);
                
//        unsigned int lectura_ADC;
//        lectura_ADC = tomamuestra_ADC(0x3C);
//        POS_CURSOR(2,0);
//        ESCRIBE_MENSAJE2("Value: ");
//        LCD_ESCRIBE_VAR_INT(lectura_ADC,3);
//        LCD_CHAR_GRADO();
    }
}



// offset is int16_t data type
// gain is int16_t data type
// ADC_MEAS is uint16_t data type
// Temp_in_C is int24_t data type
//ADC_MEAS = ((ADRESH << 8) + ADRESL); // Store the ADC Result
//Temp_in_C = (int24_t)(ADC_MEAS) * gain; // Multiply the ADC Result by
// Gain and store the result in a
// signed variable
//Temp_in_C = Temp_in_C / 256; // Divide (ADC Result * Gain) by 256
//Temp_in_C = Temp_in_C + offset; // Add (Offset) to the result
//Temp_in_C = Temp_in_C / 10; // Divide the result by 10 and