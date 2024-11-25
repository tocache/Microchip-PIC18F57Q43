#ifndef I2C_LCD_LIB_H_

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
La función I2C1_WRITESINGLEBYTE() ha sido mejorado según modificación
de Joseph López basado en el video de I2C de Wels
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

/*Función para inicializar el periférico I2C1*/
void I2C1_INIT(void);
void I2C_LCD_ADDR_SET(unsigned char configuracion);
/*Función para escribir un solo dato de un byte
 a través del periférico I2C1 donde:
 -dirección es la dirección del esclavo (sin
 incluir el bit R/W)
 -dato es el dato de ocho bits a enviar*/
void I2C1_WRITESINGLEBYTE(unsigned char direccion, unsigned char dato);
/*Función para mover el cursor fila/columna*/
void I2C_POS_CURSOR(unsigned char fila,unsigned char columna);
/*Función para apagar o encender (quitar o 
 mostrar el contenido) se usa OON para
 encendery OFF para apagar*/
void I2C_DISPLAY_ONOFF(unsigned char estado);
/*Función para mover el cursor hacia la
 primera posición en la pantalla: esquina}
 superior izquierda*/
void I2C_CURSOR_HOME(void);
/*Función para encender/apagar el cursor
 donde OON es encendido y OFF es apagado*/
void I2C_CURSOR_ONOFF(unsigned char estado);
/*Función para enviar un dato hacia el LCD*/
void I2C_ENVIA_LCD_DATA(unsigned char dato);
/*Función para borrar el contenido en la pantalla*/
void I2C_BORRAR_LCD(void);
/*Función para la configuración del LCD a
 *modo 4 bits*/
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
/*Función para inicializar el LCD que incluye la
 llamada a la función de inicialización del
 periférico I2C1 y la configuración del LCD para
 que trabaje en 4 bits*/
void I2C_LCD_INIT(void);
void I2C_LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos);
void I2C_LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto);
void I2C_LCD_CHAR_GRADO(void);
void I2C_LCD_VARCHAR_BITS(unsigned char dato);
void I2C_LCD_VARCHAR_HEX(unsigned char dato);

#endif	/* XC_HEADER_TEMPLATE_H */
