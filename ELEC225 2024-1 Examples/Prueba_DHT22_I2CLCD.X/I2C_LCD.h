#ifndef I2C_LCD_LIB_H_
/*Librer�a I2C-LCD desarrollada por Kalun Lau.
Las principales funciones para el LCD fueron basados en una
libreria desarrollada por Sergio Salas para un PIC18F4550.
Las configuraciones del perif�rico I2C1 fueron basados en
un c�digo proporcionado por Alonso S�nchez.
Las funciones de inicializaci�n, env�o de dato y env�o de
comando para el LCD se basaron en el trabajo de Vladimir 
Anglas.
Curso de Microcontroladores
Universidad Peruana de Ciencias Aplicadas
Ultima edicion 19/11/2023*/
#define	I2C_LCD_LIB_H_

#define OON  0
#define OFF 1
#define _XTAL_FREQ 32000000UL
#define  PIN_RS    0x01
#define  PIN_RW    0x02
#define  PIN_EN    0x04
#define  BACKLIGHT 0x08

/*Funci�n para inicializar el perif�rico I2C1*/
void I2C1_INIT(void);
/*Funci�n para escribir un solo dato de un byte a trav�s del
 perif�rico I2C1 donde:
 -direcci�n es la direcci�n del esclavo (sin incluir el
 *  bit R/W)
 -dato es el dato de ocho bits a enviar*/
void I2C1_WRITESINGLEBYTE(unsigned char direccion, unsigned char dato);
/*Funci�n para mover el cursor fila/columna*/
void I2C_POS_CURSOR(unsigned char fila,unsigned char columna);
/*Funci�n para apagar o encender (quitar o mostrar el contenido)
 se usa OON para encender y OFF para apagar*/
void I2C_DISPLAY_ONOFF(unsigned char estado);
/*Funci�n para mover el cursor hacia la primera posici�n en la
 pantalla: esquina superior izquierda*/
void I2C_CURSOR_HOME(void);
/*Funci�n para encender/apagar el cursor donde OON es encendido y
 OFF es apagado*/
void I2C_CURSOR_ONOFF(unsigned char estado);
/*Funci�n para enviar un dato hacia el LCD*/
void I2C_ENVIA_LCD_DATA(unsigned char dato);
/*Funci�n para borrar el contenido en la pantalla*/
void I2C_BORRAR_LCD(void);
/*Funci�n para la configuraci�n del LCD a modo 4 bits*/
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
/*Funci�n para inicializar el LCD que incluye la llamada a la funci�n
 de inicializaci�n del perif�rico I2C1 y la configuraci�n del LCD para
 que trabajo en 4 bits*/
void I2C_LCD_INIT(void);
void I2C_LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos);
void I2C_LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto);
void I2C_LCD_CHAR_GRADO(void);
void I2C_LCD_VARCHAR_BITS(unsigned char dato);
void I2C_LCD_VARCHAR_HEX(unsigned char dato);

#endif	/* XC_HEADER_TEMPLATE_H */