/*
Librería I2C-LCD desarrollada por Kalun Lau.
Las principales funciones para el LCD fueron basados en una libreria
desarrollada por Sergio Salas para un PIC18F4550.
Las configuraciones del periférico I2C1 fueron basados en un código
proporcionado por Alonso Sánchez.
Las funciones de inicialización, envío de dato y envío de comando
para el LCD se basaron en el trabajo de Vladimir Anglas.
La opción de tener la capacidad de cambiar la dirección del
I2C para poder conectar varios I2C-LCDs fué propuesta por
Ucchelly Romero.
Curso de Microcontroladores
Universidad Peruana de Ciencias Aplicadas
Lima - Peru


Changelog:
19/11/2023 Primera versión funcionando
14/06/2024 Se agrego opcion para seleccionar la direccion
del PCF8574/PCF8574A, como para usar varios LCD montados en el I2C.
La dirección esclavo I2C esta definido por la variable I2C_LCD_ADDR,
por defecto esta en 0x27 (PCF8574_7), para modificar se actualiza
I2C_LCD_ADDR para la dirección nueva.
Tener en cuenta que antes de manipular un I2C_LCD se deberá de
establecer la dirección de dicho I2C_LCD
 */

#include <xc.h>
#include "I2C_LCD.h"
#include <string.h>

unsigned char I2C_LCD_ADDR = PCF8574_7;

void I2C1_INIT(void){
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
}

void I2C_LCD_ADDR_SET(unsigned char configuracion){
    I2C_LCD_ADDR = configuracion;
}

void I2C1_WRITESINGLEBYTE(unsigned char direccion, unsigned char dato){
    I2C1CNT = 1;
    I2C1ADB1 = (direccion << 1) & 0xFE;     //slave addr + 0 (write)
    I2C1TXB = dato;                     //colocamos el dato a enviar
    I2C1CON0bits.S = 1; // START condition
    while(I2C1STAT1bits.TXBE == 0); // espera a que el buffer TX este vacio
    while(I2C1CON1bits.ACKSTAT == 1); // Espera a recibir la rpta del cliente (ACK))
    while(I2C1PIRbits.PCIF == 0); //Espera a terminar STOP condition
}

void I2C_POS_CURSOR(unsigned char fila,unsigned char columna){
	if(fila == 1){
		I2C_ENVIA_LCD_CMD(0x80+columna);
	}
	else if(fila == 2){
		I2C_ENVIA_LCD_CMD(0xC0+columna);
	}
	else if(fila == 3){
		I2C_ENVIA_LCD_CMD(0x94+columna);
	}
	else if(fila == 4){
		I2C_ENVIA_LCD_CMD(0xD4+columna);
	}
	__delay_ms(1);
}

void I2C_BLINK_CURSOR(unsigned char val){
	if(val == OFF) I2C_ENVIA_LCD_CMD(0x0E);
	if(val == OON ) I2C_ENVIA_LCD_CMD(0x0F);
}

void I2C_DISPLAY_ONOFF(unsigned char estado){
	if(estado == OON)  I2C_ENVIA_LCD_CMD(0x0F);
	if(estado == OFF) I2C_ENVIA_LCD_CMD(0x08);
}

void I2C_CURSOR_HOME(void){
	I2C_ENVIA_LCD_CMD(0x02);
}

void I2C_CURSOR_SHIFTLEFT(void){
	I2C_ENVIA_LCD_CMD(0x10);
}

void I2C_CURSOR_SHIFTRIGHT(void){
	I2C_ENVIA_LCD_CMD(0x14);
}

void I2C_DISPLAY_SHIFTLEFT(void){
	I2C_ENVIA_LCD_CMD(0x18);
}

void I2C_DISPLAY_SHIFTRIGHT(void){
	I2C_ENVIA_LCD_CMD(0x1C);
}

void I2C_CURSOR_ONOFF(unsigned char estado){	
	if(estado == OON)   I2C_ENVIA_LCD_CMD(0x0E);
	if(estado == OFF)	I2C_ENVIA_LCD_CMD(0x0C);
}

void I2C_ESCRIBE_MENSAJE(const char *cadena,unsigned char tam){
	unsigned char i = 0;
	for(i = 0; i<tam; i++)	{
		I2C_ENVIA_LCD_DATA(cadena[i]);
	}
}

void I2C_ESCRIBE_MENSAJE2(const char *cadena){
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)	{
		I2C_ENVIA_LCD_DATA(cadena[i]);
	}
}

void I2C_ENVIA_LCD_DATA(unsigned char data){
    unsigned char highnibble;
    unsigned char lownibble;
    //backlight siempre activado
    highnibble = (data & 0xF0) | BACKLIGHT;
    lownibble  = (unsigned char)(((data & 0x0F)<<4)| BACKLIGHT);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,(highnibble | PIN_EN | PIN_RS)); //habilito EN 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,(highnibble | PIN_RS)); //deshabilito EN
    __delay_us(20);

    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,(lownibble | PIN_EN | PIN_RS)); //habilito EN 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,(lownibble | PIN_RS)); //deshabilito EN
    __delay_us(20);	
}

void I2C_BORRAR_LCD(void){
	I2C_ENVIA_LCD_CMD(0x01);
    __delay_ms(50);
}

void I2C_ENVIA_LCD_CMD(unsigned char command){
    unsigned char highnibble;
    unsigned char lownibble;
    
    highnibble = (command & 0xF0) | BACKLIGHT;
    lownibble  = (unsigned char)(((command & 0x0F)<<4)| BACKLIGHT);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,(highnibble | PIN_EN)); //habilito EN 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,highnibble); //deshabilito EN
    __delay_us(20);

    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,(lownibble | PIN_EN)); //habilito EN 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,lownibble); //deshabilito EN
    __delay_us(20);
}

void I2C_GENERACARACTER(const unsigned char *vector,unsigned char pos){
	unsigned char i;
	I2C_ENVIA_LCD_CMD(0x40+8*pos);//Dirección de la CGRAM +
    __delay_us(20);
	for(i=0;i<8;i++)			 //offset de posición de caracter	
	{
		I2C_ENVIA_LCD_DATA(vector[i]);
        __delay_us(120);
	}
	I2C_ENVIA_LCD_CMD(0x80);	//Dirección de la DDRAM
    __delay_us(20);
}

void I2C_LCD_INIT(void){
    I2C1_INIT();
    __delay_ms(15);

    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00);
    __delay_ms(1000);

    //MANDO 3 VECES ESTE DATO
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x34);    
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30);     
    __delay_ms(5);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x34);   
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30);

    __delay_ms(5);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30);
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x34);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x30);
    
    __delay_us(250);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x20);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x24);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x20); 
    
    __delay_us(75);

    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x20);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x24);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x20); 
    
    __delay_us(75);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x80);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x84);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x80); 
    
    __delay_us(75); 
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x04); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00); 
    
     __delay_us(75);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0xC0); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0xC4); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0xC0); 
    
     __delay_us(75);
 
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x04); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00);

     __delay_us(75);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x10); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x14);  
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x10); 
    
     __delay_ms(2);
 
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00); 
    __delay_us(02);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x04);   
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00); 
     
     __delay_us(75);
 
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x60); 
    __delay_us(02);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x64);
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x60);

     __delay_us(75);
   
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x04); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x00);
    
    __delay_us(75);
    
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x20); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x24); 
    __delay_us(20);
    I2C1_WRITESINGLEBYTE(I2C_LCD_ADDR,0x20);

    __delay_ms(15);
    I2C_BORRAR_LCD();
    I2C_CURSOR_HOME();
    I2C_CURSOR_ONOFF(OFF);
}

//funcion para visualizar una variable de 8 bits en formato decimal
void I2C_LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos){
    unsigned char centena, decena, unidad;  //variables de funcion convierte
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            I2C_ENVIA_LCD_DATA(unidad+0x30);
            break;
        case 2:
            I2C_ENVIA_LCD_DATA(decena+0x30);
            I2C_ENVIA_LCD_DATA(unidad+0x30);
            break;
        case 3:
            I2C_ENVIA_LCD_DATA(centena+0x30);
            I2C_ENVIA_LCD_DATA(decena+0x30);
            I2C_ENVIA_LCD_DATA(unidad+0x30);
            break;
    }
}

void I2C_LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto){
    unsigned char d_millar, millar, centena, decena, unidad;  //variables de funcion convierte
    d_millar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            I2C_ENVIA_LCD_DATA(unidad+0x30);
            break;
        case 2:
            if(punto == 0){
                I2C_ENVIA_LCD_DATA(decena+0x30);
                I2C_ENVIA_LCD_DATA(unidad+0x30);
            }
            else if(punto == 1){
                I2C_ENVIA_LCD_DATA(decena+0x30);
                I2C_ENVIA_LCD_DATA('.');
                I2C_ENVIA_LCD_DATA(unidad+0x30);
            }
            break;
        case 3:
            switch(punto){
                case 0:
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 1:
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 2:
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
            }
            break;
        case 4:
            switch(punto){
                case 0:
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 1:
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 2:
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 3:
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
            }
            break;
        case 5:
            switch(punto){
                case 0:
                    I2C_ENVIA_LCD_DATA(d_millar+0x30);
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 1:
                    I2C_ENVIA_LCD_DATA(d_millar+0x30);
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 2:
                    I2C_ENVIA_LCD_DATA(d_millar+0x30);
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 3:
                    I2C_ENVIA_LCD_DATA(d_millar+0x30);
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
                case 4:
                    I2C_ENVIA_LCD_DATA(d_millar+0x30);
                    I2C_ENVIA_LCD_DATA('.');
                    I2C_ENVIA_LCD_DATA(millar+0x30);
                    I2C_ENVIA_LCD_DATA(centena+0x30);
                    I2C_ENVIA_LCD_DATA(decena+0x30);
                    I2C_ENVIA_LCD_DATA(unidad+0x30);
                    break;
            }
            break;
    }
}

void I2C_LCD_CHAR_GRADO(void){
    I2C_ENVIA_LCD_DATA(0xDF);
}

//funcion para visualizar una variable de 8 bits en formato binario
void I2C_LCD_VARCHAR_BITS(unsigned char dato){
    I2C_ENVIA_LCD_DATA('0');
    I2C_ENVIA_LCD_DATA('b');
    unsigned char x_var;
    for(x_var=0;x_var<8;x_var++){
        if (((dato >> (7 - x_var)) & 0x01) == 1){
            I2C_ENVIA_LCD_DATA('1');
        }
        else{
            I2C_ENVIA_LCD_DATA('0');
        }
    }
}

//funcion para visualizar una variable de 8 bits en formato hexadecimal
void I2C_LCD_VARCHAR_HEX(unsigned char dato){
    unsigned char high_nib, low_nib;
    I2C_ENVIA_LCD_DATA('0');
    I2C_ENVIA_LCD_DATA('x');
    high_nib = (dato >> 4) & 0x0F;
    low_nib = dato & 0x0F;
    switch(high_nib){
        case 0 ... 9:
            I2C_ENVIA_LCD_DATA(high_nib+0x30);
            break;
        case 10 ... 15:
            I2C_ENVIA_LCD_DATA(high_nib+0x37);
            break;
    }
    switch(low_nib){
        case 0 ... 9:
            I2C_ENVIA_LCD_DATA(low_nib+0x30);
            break;
        case 10 ... 15:
            I2C_ENVIA_LCD_DATA(low_nib+0x37);
            break;
    }
}