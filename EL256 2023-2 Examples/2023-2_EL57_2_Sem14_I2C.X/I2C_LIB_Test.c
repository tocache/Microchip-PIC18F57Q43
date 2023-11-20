#include "I2C_LIB_Test.h"

void ESCRIBIR_PCF8574(unsigned char dato){
    unsigned char temporal;
    temporal = dato;
    
    I2C1_WriteSingleByte(0x27, dato);
}


