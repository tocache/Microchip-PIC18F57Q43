/*
 * LCD: envia un mensaje de prueba
 * Conexiones: LCD: RS  RW  E    D4  D5  D6  D7
 *             PIC: RC0 RC1 RC2  RC4 RC5 RC6 RC7
 * Author: Javier Barriga Hoyle
 */

#include <xc.h>
#include "main.h"
#include "configuracion.h"

// Defino algunos valores importantes para el LCD
#define RS LATC0            // LATD.0 asignado a RS del LCD
#define WR LATC1            // LATD.1 asignado a R/W del LCD
#define EN LATC2            // LATD.2 asignado a EN del LCD
#define ldata LATC          // PORTD(PD4-PD7) asignado para LCD envío datos 

// Defino prototipos
void LCD_Inicio(void);              // Inicializo LCD
void LCD_Comando(unsigned char);    // Envía comando al LCD
void LCD_Data(unsigned char x);     // Envía data al LCD
void LCD_Cadena(const char *);      // Muestra una cadena o mensaje en LCD
void LCD_Gotoxy(char fila, char columna);  // Ubica el cursor en fila,columna              
void LCD_Borra();                   // Borra pantalla LCD
void PrintNumLCD(float numero, unsigned char fila, unsigned char columna);

// defino mensajes
char Mensaje1[40] = {"Universidad UPC"};	// fila 1
char Mensaje2[40] = {"Ciclo 2025-2"};       // fila 2

// defino variables globales
int i,j;

void main(void)
{
//configuro puertos como entradas o salidas
    TRISC = 0x00;                   // PUERTO D como salida.
    ANSELC = 0x00;
            
	LCD_Inicio();                   // inicializo LCD

	/* envio mensaje1 */
		LCD_Gotoxy(1,2);            // posiciono cursor en la fila 1, columna 0
		for(j=0; j<15; j++)
		{
			LCD_Data(Mensaje1[j]);
			__delay_ms(25);
		}
		__delay_ms(500);           // espero 2 segundos

	/* envio mensaje2 */
		LCD_Gotoxy(2,3);            // posiciono cursor en la fila 2, columna 0
		for(j=0; j<12; j++)
		{
			LCD_Data(Mensaje2[j]);
			__delay_ms(25);
		}
        __delay_ms(500);           // espero 3 segundos
//    LCD_Borra();                    // Borra pantalla   

    LCD_Gotoxy(3,1);                // Se posiciona cursor
    LCD_Cadena("MICROCONTROLADORES");
    LCD_Gotoxy(4,2);                // Se posiciona cursor
    LCD_Cadena("1AEL0256 - 13509");
            
    while(1); // microcontrolador no puede parar
} //fin de main

/*area de funciones*/
/*--------------------------------------------------------------------
Función: void InitLcd(void)
	Inicializa el display LCD.
--------------------------------------------------------------------*/
void LCD_Inicio(void)
{
    __delay_ms(15);             // Espera de 15 ms
	LATC= 0x30;                 // DB[7..4]	 X	EN  R/W RS 
								//    0011	 0	 0   0	 0 
	EN = 1;                     // Genero pulso en EN (1-to-0) 
	NOP();                      // Retarda un ciclo
	EN = 0;
	__delay_ms(5);              // Demora superior a 4,1 msg

	LATC= 0x30;                 // DB[7..4]	 X	EN  R/W RS 
								//    0011	 0	 0   0	 0 
	EN = 1;                     // Genero pulso en EN (1-to-0) 
	NOP();                      // Retarda un ciclo
	EN = 0;
    __delay_ms(1);              // Demora superior a 100 useg

	LATC= 0x30;                 // DB[7..4]	 X	EN  R/W RS 
								//    0011	 0	 0   0	 0 
	EN = 1;                     // Genero pulso en EN (1-to-0) 
	NOP();                      // Retarda un ciclo
	EN = 0;
	__delay_ms(1);              // Demora superior a 100 useg

/* Tras esta inicialización el display configuramos LCD en modo 4 bits */
    LCD_Comando(0x02);          // Configuro en modo 4 bits
    LCD_Comando(0x28);          // Usa 2 lineas y matriz de 5x7 
    LCD_Comando(0x01);          // Borra display
    LCD_Comando(0x0c);          // Display ON, cursor OFF
	LCD_Comando(0x06);          // Incrementa cursor y desplaza a la derecha
} // FIN DE LcdInicio

/*---------------------------------------------------------------------------
Función: void  LCD_Comando(unsigned char cmd)
Envia al display LCD un comando para acceder al registro de instrucciones.
-----------------------------------------------------------------------------*/
void LCD_Comando(unsigned char cmd)
{
	ldata = (ldata & 0x0f) |(0xF0 & cmd);   // Envía nibble alto al PORT 
	RS = 0;                                 // RS=0 selecciona registro comandos 
	EN = 1;                                 // Genero pulso en EN (1-to-0)  
	NOP();
	EN = 0;
	__delay_ms(1);
    ldata = (ldata & 0x0f) | (cmd<<4);      // Envía nibble bajo al PORT
	EN = 1;                                 // Genero pulso en EN (1-to-0)
	NOP();
	EN = 0;
	__delay_ms(3);
}

/*---------------------------------------------------------------------------
Función: void  LCD_Data(unsigned char data)
Envia al display LCD un dato para acceder al registro de datos.
-----------------------------------------------------------------------------*/
void LCD_Data(unsigned char dat)
{
	ldata = (ldata & 0x0f) | (0xF0 & dat);      // Envía nibble alto al PORT
	RS = 1;                                     // RS=1 selecciona registro datos
	EN = 1;                                     // Genero pulso en EN (1-to-0)
	NOP();
	EN = 0;
	__delay_ms(1);
    ldata = (ldata & 0x0f) | (dat<<4);          // Envía nibble bajo al PORT
	EN = 1;                                     // Genero pulso en EN (1-to-0)
	NOP();
	EN = 0;
	__delay_ms(3);
}

/*---------------------------------------------------------------------------
Función: void  LCD_Cadena(unsigned char *msg)
Envia al display LCD una cadena o mensaje.
-----------------------------------------------------------------------------*/
void LCD_Cadena(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Data(*msg);
	  msg++;	
    }
}

/*---------------------------------------------------------------------------
Funcion:  void LCD_Gotoxy(char fila, char columna)
	Posiciona el cursor en la posicion especificada por fila,columna.
	Si alguna de las coordenadas es invalida no se hace nada.
	Coordenadas validas: fila  = 1..2, columna = 1..20
----------------------------------------------------------------------------*/
void LCD_Gotoxy(char fila, char columna){
    char posicion=0;
    switch(fila){
        case 1:
            posicion=(0x80) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
        case 2:
            posicion=(0xc0) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
        case 3:
            posicion=(0x94) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
        case 4:
            posicion=(0xd4) | (columna & 0x0f);
            LCD_Comando(posicion);
            break;
    }
}

/*--------------------------------------------------------------------
Funcion:  void LCD_Borra(void)
	Limpia pantalla y pone el cursor en el origen.
--------------------------------------------------------------------*/
void LCD_Borra()
{
   	LCD_Comando(0x01);      // Comando para borrar
    __delay_ms(3);
}

/********************************************************************************
Funcion: void PrintNumLCD(float numero, UCHAR fila, UCHAR columna)
Imprime en el LCD un número en punto flotante con el formato
(x.xxxx), en la posición especificada por fila y columna.
********************************************************************************/
/*
void PrintNumLCD(float numero, unsigned char fila, unsigned char columna)
{
    unsigned int cuenta;
    LCD_Gotoxy(fila, columna);        // Posiciona cursor al inicio de la fila 2
// Se imprime en el LCD
    num = (long) ( voltios * 100000 / 1);
    cociente = num / 100000;                // Divide y toma la parte entera
    residuo = num % 100000;                 // Divide y toma el residuo
    LCD_Data(cociente + 0x30);              // Convierte a ASCII e imprime en LCD
    LCD_Data('.');                          // Imprime punto decimal
    divisor = 10000;
    for(cuenta=2; cuenta<7; cuenta++){
        cociente = (residuo / divisor);     // Divide y toma la parte entera
        residuo = residuo % divisor;        // Divide y toma el residuo
        LCD_Data(cociente + 0x30);          // Convierte a ASCII e imprime en LCD
        divisor = divisor /10;
    }
}*/   