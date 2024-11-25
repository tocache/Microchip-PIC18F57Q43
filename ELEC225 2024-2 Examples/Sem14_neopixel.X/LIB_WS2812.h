/*
Librería WS2812 desarrollada por Kalun Lau para ser usado con
el microcontrolador PIC18F57Q43 y PIC18F57Q84.
La formación de la trama de datos para el WS2812 se basó en
una implementacion usando SPI, Timer2, CCP en PWM y CLB
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
