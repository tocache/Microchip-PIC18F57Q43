/* 
 * File:   LIB_DHT.h
 * Author: upao
 *
 * Created on 10 de junio de 2024, 03:49 PM
 */

/* Librería desarrollada por Kalun Lau en base a
un ejemplo de interface que no me acuerdo en donde lo ví

Changelog:
17/11/2025 He creado una nueva función en base a struct
para que retorne las dos medidas (temperatura y humedad)
en base a una sola acción de lectura del sensor.

La función ejemplo sería asi:
struct DHT_Values actuales = DHT_GetBoth(DHT11);
Para sacar el valor de temperatura:
actuales.DHT_Temp
Para sacar el valor de humedad:
actuales.DHT_Humid

25/11/2024 Le coloqué una opción rudimentaria de timeout
para que no se quede colgado el programa en los whiles
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

struct DHT_Values{
    unsigned int DHT_Temp;
    unsigned int DHT_Humid;
};

/*Función para obtener los valores de humedad relativa y temperatura
 del DHTxx en una sola acción de lectura al sensor.
 Tener en cuenta que para el DHT22 se deberá de dividir entre 10
 el valor obtenido*/
struct DHT_Values DHT_GetBoth(unsigned char modelo);

#endif	/* LIB_DHT_H */


