#include "mcc_generated_files/system/system.h"
#include "LIB_DHT.h"

float HCSR04_GetDistance(void){
    //condiciones inicial
    Timer0_CounterSet(0x0000);
    //envio del pulso de 10us por TRIG
    TRIG_SetHigh();
    __delay_us(10);
    TRIG_SetLow();
    //medir el tiempo del ancho positivo de la señal de ECHO
    while(!ECHO_GetValue());
    Timer0_Start();
    while(ECHO_GetValue());
    Timer0_Stop();
    return (Timer0_CounterGet() / 58.31);
}

int main(void){
    SYSTEM_Initialize();
    while(1){
        UART1_String_Write("MIERCOLEEEEEEEEES");
        UART1_NewLine();
        UART1_String_Write("Este es el ultimo proyecto en el PIC18F57Q43");
        UART1_NewLine();
        UART1_String_Write("Siguiente semestre se usara el PIC18F47Q10");
        UART1_NewLine();
        UART1_String_Write("Variable de 8bit: ");
        UART1_8bitVar_Write(189);
        UART1_NewLine();
        UART1_String_Write("Variable de 16bit: ");
        UART1_16bitVar_Write(60666);
        UART1_NewLine();
        UART1_String_Write("Variable float: ");
        UART1_Float_Write(321.1234,4);
        UART1_NewLine();
        //sector para leer distancia con el HCSR04
        UART1_String_Write("Distancia HCSR04: ");
        float medida = HCSR04_GetDistance();
        if(medida >=100){
            UART1_Float_Write(medida/100,2);
            UART1_String_Write(" m");
            LED_SetHigh();
        }
        else{
            UART1_Float_Write(medida,3);
            UART1_String_Write(" cm");
            LED_SetLow();
        }
        UART1_NewLine();
        //sector para leer temperatura y humedad del DHT11
        struct DHT_Values mediciones = DHT_GetBoth(DHT11);
        UART1_String_Write("Temperatura DHT11: ");
        UART1_16bitVar_Write2(mediciones.DHT_Temp,2);
        UART1_String_Write(" °C");
        UART1_NewLine();
        UART1_String_Write("Humedad DHT11: ");
        UART1_16bitVar_Write2(mediciones.DHT_Humid,2);
        UART1_String_Write(" %RH");
        UART1_NewLine();
        __delay_ms(2000);
    }    
}