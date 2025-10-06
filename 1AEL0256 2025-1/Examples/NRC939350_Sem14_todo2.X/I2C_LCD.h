#ifndef I2C_LCD_LIB_H_

/*
Librer�a I2C-LCD desarrollada por Kalun Lau.
Las principales funciones para el LCD fueron basados en una libreria
desarrollada por Sergio Salas para un PIC18F4550.
Las configuraciones del perif�rico I2C1 fueron basados en un c�digo
proporcionado por Alonso S�nchez.
Las funciones de inicializaci�n, env�o de dato y env�o de comando
para el LCD se basaron en el trabajo de Vladimir Anglas.
La opci�n de tener la capacidad de cambiar la direcci�n del
I2C para poder conectar varios I2C-LCDs fu� propuesta por
Ucchelly Romero.
La funci�n I2C1_WRITESINGLEBYTE() ha sido mejorado seg�n modificaci�n
de Joseph L�pez basado en el video de I2C de Wels
Curso de Microcontroladores
Universidad Peruana de Ciencias Aplicadas
Lima - Peru


Changelog:
19/11/2023 Primera versi�n funcionando
14/06/2024 Se agrego opcion para seleccionar la direccion
del PCF8574/PCF8574A, como para usar varios LCD montados en el I2C.
La direcci�n esclavo I2C esta definido por la variable I2C_LCD_ADDR,
por defecto esta en 0x27 (PCF8574_7), para modificar se actualiza
I2C_LCD_ADDR para la direcci�n nueva.
Tener en cuenta que antes de manipular un I2C_LCD se deber� de
establecer la direcci�n de dicho I2C_LCD
 */

#define	I2C_LCD_LIB_H_

#define OON  0
#define OFF 1
#define _XTAL_FREQ 32000000UL
#define PIN_RS    0x01
#define PIN_RW    0x02
#define PIN_EN    0x04
#define BACKLIGHT 0x08
#define PCF8574_7 0x27
#define PCF8574_6 0x26
#define PCF8574_5 0x25
#define PCF8574_4 0x24
#define PCF8574_3 0x23
#define PCF8574_2 0x22
#define PCF8574_1 0x21
#define PCF8574_0 0x20
#define PCF8574A_7 0x3F
#define PCF8574A_6 0x3E
#define PCF8574A_5 0x3D
#define PCF8574A_4 0x3C
#define PCF8574A_3 0x3B
#define PCF8574A_2 0x3A
#define PCF8574A_1 0x39
#define PCF8574A_0 0x38

/*Funci�n para inicializar el perif�rico I2C1*/
void I2C1_INIT(void);
void I2C_LCD_ADDR_SET(unsigned char configuracion);
/*Funci�n para escribir un solo dato de un byte
 a trav�s del perif�rico I2C1 donde:
 -direcci�n es la direcci�n del esclavo (sin
 incluir el bit R/W)
 -dato es el dato de ocho bits a enviar*/
void I2C1_WRITESINGLEBYTE(unsigned char direccion, unsigned char dato);
/*Funci�n para mover el cursor fila/columna*/
void I2C_POS_CURSOR(unsigned char fila,unsigned char columna);
/*Funci�n para apagar o encender (quitar o 
 mostrar el contenido) se usa OON para
 encendery OFF para apagar*/
void I2C_DISPLAY_ONOFF(unsigned char estado);
/*Funci�n para mover el cursor hacia la
 primera posici�n en la pantalla: esquina}
 superior izquierda*/
void I2C_CURSOR_HOME(void);
/*Funci�n para encender/apagar el cursor
 donde OON es encendido y OFF es apagado*/
void I2C_CURSOR_ONOFF(unsigned char estado);
/*Funci�n para enviar un dato hacia el LCD*/
void I2C_ENVIA_LCD_DATA(unsigned char dato);
/*Funci�n para borrar el contenido en la pantalla*/
void I2C_BORRAR_LCD(void);
/*Funci�n para la configuraci�n del LCD a
 *modo 4 bits*/
void I2C_LCD_CONFIG(void);
/*Funci�n para enviar un comando hacia el LCD*/
void I2C_ENVIA_LCD_CMD(unsigned char dato);
/*Funci�n para el efecto de visualizaci�n del cursor donde: OON
 es para que se encuentre parpadeando y OFF para mostrarlo de
 manera s�lida*/
void I2C_BLINK_CURSOR(unsigned char val);
/*Funci�n para grabar un caracter personalizado en la CGRAM del
 LCD, tener en cuenta que solo se puede tener ocho caracteres
 personalizados, del 0 al 7*/
void I2C_GENERACARACTER(const unsigned char *vector,unsigned char pos);
/*Funci�n para escribir una cadena de caracteres en la pantalla,
 el par�metro tam es el n�mero de caracteres que tiene la cadena*/
void I2C_ESCRIBE_MENSAJE(const char *cadena,unsigned char tam);
/*Funci�n mejorada para escribir una cadena de caracteres en la
 pantalla, no requiere del par�metro tam para el tama�o de la
 cadena puesto a que se esta usando la funci�n strlen de la
 librer�a string.h*/
void I2C_ESCRIBE_MENSAJE2(const char *cadena);
void I2C_CURSOR_SHIFTLEFT(void);
void I2C_CURSOR_SHIFTRIGHT(void);
void I2C_DISPLAY_SHIFTLEFT(void);
void I2C_DISPLAY_SHIFTRIGHT(void);
/*Funci�n para inicializar el LCD que incluye la
 llamada a la funci�n de inicializaci�n del
 perif�rico I2C1 y la configuraci�n del LCD para
 que trabaje en 4 bits*/
void I2C_LCD_INIT(void);
void I2C_LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos);
void I2C_LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto);
void I2C_LCD_CHAR_GRADO(void);
void I2C_LCD_VARCHAR_BITS(unsigned char dato);
void I2C_LCD_VARCHAR_HEX(unsigned char dato);

#endif	/* XC_HEADER_TEMPLATE_H */