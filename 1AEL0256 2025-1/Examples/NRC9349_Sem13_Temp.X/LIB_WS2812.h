/*
Librer�a WS2812 desarrollada por Kalun Lau para ser usado con
el microcontrolador PIC18F57Q43 y PIC18F57Q84.
La formaci�n de la trama de datos para el WS2812 se bas� en
una implementacion usando SPI, Timer2, CCP en PWM y CLB que hizo
Microchip en el siguiente ejemplo para el PIC16F13145 (https://github.com/microchip-pic-avr-examples/pic16f13145-spi-ws2812-mplab-mcc).
Video de referencia (emplea el MCC): https://www.youtube.com/watch?v=hHLMnJs87VE
Documento de referencia para el protocolo del WS2812: http://ww1.microchip.com/downloads/en/AppNotes/00001606A.pdf

Para esta implementaci�n no se us� el MCC ni el Melody, esta hecho con pura configuraci�n de registros y c�digo en C.

Curso de Microcontroladores
Universidad Peruana de Ciencias Aplicadas
Lima - Peru

Changelog:
25/11/2024 Creaci�n de la librer�a
 */

#ifndef LIB_WS2812_H
#define	LIB_WS2812_H

/*Funci�n de inicializaci�n de
 comunicaci�n para WS2812*/
void WS2812_INIT(void);

/*Funci�n para enviar datos de
los colores del WS2812*/
void WS2812_DATA_SEND(unsigned char green, unsigned char red, unsigned char blue);

#endif	/* LIB_WS2812_H */