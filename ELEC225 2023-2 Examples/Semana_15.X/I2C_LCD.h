#ifndef I2C_LCD_LIB_H_
/*Librería I2C-LCD desarrollada por Kalun Lau.
Las principales funciones para el LCD fueron basados en una
libreria desarrollada por Sergio Salas para un PIC18F4550.
Las configuraciones del periférico I2C1 fueron basados en
un código proporcionado por Alonso Sánchez.
Las funciones de inicialización, envío de dato y envío de
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

/*Función para inicializar el periférico I2C1*/
void I2C1_INIT(void);
/*Función para escribir un solo dato de un byte a través del
 periférico I2C1 donde:
 -dirección es la dirección del esclavo (sin incluir el
 *  bit R/W)
 -dato es el dato de ocho bits a enviar*/
void I2C1_WRITESINGLEBYTE(unsigned char direccion, unsigned char dato);
/*Función para mover el cursor fila/columna*/
void I2C_POS_CURSOR(unsigned char fila,unsigned char columna);
/*Función para apagar o encender (quitar o mostrar el contenido)
 se usa OON para encender y OFF para apagar*/
void I2C_DISPLAY_ONOFF(unsigned char estado);
/*Función para mover el cursor hacia la primera posición en la
 pantalla: esquina superior izquierda*/
void I2C_CURSOR_HOME(void);
/*Función para encender/apagar el cursor donde OON es encendido y
 OFF es apagado*/
void I2C_CURSOR_ONOFF(unsigned char estado);
/*Función para enviar un dato hacia el LCD*/
void I2C_ENVIA_LCD_DATA(unsigned char dato);
/*Función para borrar el contenido en la pantalla*/
void I2C_BORRAR_LCD(void);
/*Función para la configuración del LCD a modo 4 bits*/
void I2C_LCD_CONFIG(void);
/*Función para enviar un comando hacia el LCD*/
void I2C_ENVIA_LCD_CMD(unsigned char dato);
/*Función para el efecto de visualización del cursor donde: OON
 es para que se encuentre parpadeando y OFF para mostrarlo de
 manera sólida*/
void I2C_BLINK_CURSOR(unsigned char val);
/*Función para grabar un caracter personalizado en la CGRAM del
 LCD, tener en cuenta que solo se puede tener ocho caracteres
 personalizados, del 0 al 7*/
void I2C_GENERACARACTER(const unsigned char *vector,unsigned char pos);
/*Función para escribir una cadena de caracteres en la pantalla,
 el parámetro tam es el número de caracteres que tiene la cadena*/
void I2C_ESCRIBE_MENSAJE(const char *cadena,unsigned char tam);
/*Función mejorada para escribir una cadena de caracteres en la
 pantalla, no requiere del parámetro tam para el tamaño de la
 cadena puesto a que se esta usando la función strlen de la
 librería string.h*/
void I2C_ESCRIBE_MENSAJE2(const char *cadena);
void I2C_CURSOR_SHIFTLEFT(void);
void I2C_CURSOR_SHIFTRIGHT(void);
void I2C_DISPLAY_SHIFTLEFT(void);
void I2C_DISPLAY_SHIFTRIGHT(void);
/*Función para inicializar el LCD que incluye la llamada a la función
 de inicialización del periférico I2C1 y la configuración del LCD para
 que trabajo en 4 bits*/
void I2C_LCD_INIT(void);
void I2C_LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos);
void I2C_LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto);
void I2C_LCD_CHAR_GRADO(void);
void I2C_LCD_VARCHAR_BITS(unsigned char dato);
void I2C_LCD_VARCHAR_HEX(unsigned char dato);

#endif	/* XC_HEADER_TEMPLATE_H */