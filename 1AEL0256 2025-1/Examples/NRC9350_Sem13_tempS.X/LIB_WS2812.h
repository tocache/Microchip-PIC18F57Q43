/*
Librería WS2812 desarrollada por Kalun Lau para ser usado con
el microcontrolador PIC18F57Q43 y PIC18F57Q84.
La formación de la trama de datos para el WS2812 se basó en
una implementacion usando SPI, Timer2, CCP en PWM y CLB que hizo
Microchip en el siguiente ejemplo para el PIC16F13145 (https://github.com/microchip-pic-avr-examples/pic16f13145-spi-ws2812-mplab-mcc).
Video de referencia (emplea el MCC): https://www.youtube.com/watch?v=hHLMnJs87VE
Documento de referencia para el protocolo del WS2812: http://ww1.microchip.com/downloads/en/AppNotes/00001606A.pdf

Para esta implementación no se usó el MCC ni el Melody, esta hecho con pura configuración de registros y código en C.

Curso de Microcontroladores
Universidad Peruana de Ciencias Aplicadas
Lima - Peru

Changelog:
25/11/2024 Creación de la librería
 */

#ifndef LIB_WS2812_H
#define	LIB_WS2812_H

/*Función de inicialización de
 comunicación para WS2812*/
void WS2812_INIT(void);

/*Función para enviar datos de
los colores del WS2812*/
void WS2812_DATA_SEND(unsigned char green, unsigned char red, unsigned char blue);

#endif	/* LIB_WS2812_H */