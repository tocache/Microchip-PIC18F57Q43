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
        UART1_String_Write("Hola mundo, es la semana 14");
        UART1_NewLine();
        UART1_String_Write("Microcontroladores PIC18F57Q43");
        UART1_NewLine();
        UART1_String_Write("Penultimo ejercicio con el PIC18F57Q43");
        UART1_NewLine();
        UART1_String_Write("Prueba impresion variable 8bit: ");
        UART1_8bitVar_Write(149);
        UART1_NewLine();
        UART1_String_Write("Prueba impresion variable 16bit: ");
        UART1_16bitVar_Write(54321);
        UART1_NewLine();
        UART1_String_Write("Prueba impresion variable float: ");
        UART1_Float_Write(321.1245,4);
        UART1_NewLine();
        struct DHT_Values medidas = DHT_GetBoth(DHT11);
        UART1_String_Write("Temperatura DHT11: ");
        UART1_16bitVar_Write2(medidas.DHT_Temp,2);
        UART1_String_Write(" °C");
        UART1_NewLine();
        UART1_String_Write("Humedad DHT11: ");
        UART1_16bitVar_Write2(medidas.DHT_Humid,2);
        UART1_String_Write(" %RH");
        UART1_NewLine();
        if(medidas.DHT_Humid >= 70){
            LED1_SetHigh();
        }
        else{
            LED1_SetLow();
        }
        //ahora lectura de hcsr04
        UART1_String_Write("Distancia HCSR04: ");
        UART1_Float_Write(HCSR04_GetDistance(),3);
        UART1_String_Write(" cm");
        UART1_NewLine();
        __delay_ms(2000);
    }    
}