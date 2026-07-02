#include "mcc_generated_files/system/system.h"
#include "LIB_DHT.h"

bool estado;

float Lectura_HCSR04(void){
    //cuenta de Timer0 en cero
    Timer0_CounterSet(0x0000);
    //envio del pulso de 10us a TRIG
    TRIG_SetHigh();
    __delay_us(10);
    TRIG_SetLow();
    //toma del tiempo del pulso en ECHO
    while(!ECHO_GetValue());
    Timer0_Start();
    while(ECHO_GetValue());
    Timer0_Stop();
    //calculo de la distancia en centimetros
    return (Timer0_CounterGet() / 58.31);
}

int main(void){
    SYSTEM_Initialize();
    while(1){
        UART1_String_Write("Hola mundo!");
        UART1_NewLine();
        UART1_String_Write("Ultimo laboratorio de Micro");
        UART1_NewLine();
        UART1_String_Write("Hecho por Kalun");
        UART1_NewLine();
        UART1_String_Write("Semestre 2026-1");
        UART1_NewLine();
        UART1_String_Write("Variable de 8bit: ");
        UART1_8bitVar_Write(149);
        UART1_NewLine();
        UART1_String_Write("Variable de 16bit: ");
        UART1_16bitVar_Write(59876);
        UART1_NewLine();
        UART1_String_Write("Variable float: ");
        UART1_Float_Write(235.3265,3);
        UART1_NewLine();
        if(!BOTON_GetValue()){
            estado = !estado;
            while(!BOTON_GetValue());
        }
        UART1_String_Write("Estado de BOTON: ");
        UART1_8bitVar_Write2(estado,1);
        UART1_NewLine();
        UART1_String_Write("Distancia HCSR04: ");
        float medida;
        medida = Lectura_HCSR04();
        if(medida < 100){
            UART1_Float_Write(medida,3);
            UART1_String_Write(" cm");
        }
        else{
            UART1_Float_Write((medida/100),2);
            UART1_String_Write(" m");
        }
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
        __delay_ms(2000);
    }    
}