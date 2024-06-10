/* 
 * File:   LIB_DHT.h
 * Author: upao
 *
 * Created on 10 de junio de 2024, 03:49 PM
 */

#ifndef LIB_DHT_H
#define	LIB_DHT_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ 32000000UL
#define DHT11 0
#define DHT22 1

/*Función para la etapa de inicio de comunicacion con el DHTxx*/
void DHT_Start(unsigned char modelo);

/*Función para ver si el DHTxx esta disponible DHTxx*/
void DHT_Check(unsigned char modelo);

/*Función para hacer lectura de un dato de 8 bits del DHTxx*/
unsigned char DHT_Read(unsigned char modelo);

/*Función para obtener el valor de temperatura del DHTxx
 Tener en cuenta que para el DHT22 se deberá de dividir entre 10
 el valor obtenido*/
unsigned int DHT_GetTemp(unsigned char modelo);

/*Función para obtener el valor de humedad relativa del DHTxx
 Tener en cuenta que para el DHT22 se deberá de dividir entre 10
 el valor obtenido*/
unsigned int DHT_GetHumid(unsigned char modelo);

#endif	/* LIB_DHT_H */

