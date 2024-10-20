/*
 * File:   MAX7219.c
 * Author: klnla
 *
 * Created on 19 de octubre de 2024, 10:26 PM
 */

#include <xc.h>
#include "MAX7219.h"

void MAX7219_Init(void){
    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSELC0 = 0;
    TRISE = 0xFC;
    ANSELE = 0xFC;
    MAX7219_WriteData2(COM_SHUTDOWN, 0x00);      //shutdown on
    MAX7219_WriteData2(COM_TEST, 0x00);      //display test off
    MAX7219_WriteData2(COM_INTENSITY, 0x03);      //intensity
    MAX7219_WriteData2(COM_SCANLIMIT, 0x07);      //scan limit
    MAX7219_WriteData2(COM_SHUTDOWN, 0x01);      //shutdown off
    MAX7219_WriteData2(COM_DECMODE, 0x00);      //decode mode (no decode)    
}

/*Esta función fué adaptada de codigoelectronica
 *(https://github.com/codigoelectronica/EjerciciosMPlabXC8/blob/master/max7219-display-7-segmentos.X/max7219.h)
 *junto con el código de Kalun Lau donde hizo interface con
 *el 74HC595, este de aquí utiliza una concatenación de comando y dato
 *y se envia los 16 bits dentro de la rutina FOR*/
void MAX7219_WriteData(unsigned char comando, unsigned char dato){
	//condiciones iniciales de la comunicación
    unsigned int temporal_data, tmp_int;
	unsigned char var_x;
	max7219_cs = 1;
	max7219_clk = 0;
	max7219_data = 0;
    temporal_data = (comando << 8) + dato;
	//inicio de la comunicacion
	max7219_cs = 0;
	for(var_x=0;var_x<16;var_x++){
		tmp_int = 1;
        tmp_int = (tmp_int << (15 - var_x));
        if((tmp_int & temporal_data) != 0){
			max7219_data = 1;
		}
		else{
			max7219_data = 0;
		}
		max7219_clk = 1;
        //__delay_us(1);
		max7219_clk = 0;
	}
	max7219_cs = 1;
}

/*Esta función fué hecha por Kalun Lau
 *a partir de un código que se hizo para
 *comunicarse con un IC 74HC595 */
void MAX7219_WriteData2(unsigned char comando, unsigned char dato){
	//condiciones iniciales de la comunicación
	unsigned char var_x;
	max7219_cs = 1;
	max7219_clk = 0;
	max7219_data = 0;
	//inicio de la comunicacion
	max7219_cs = 0;
	//envio del comando
	for(var_x=0;var_x<8;var_x++){
        max7219_clk = 0;
		if(comando & (1<<(7-var_x))){
			max7219_data = 1;
		}
		else{
			max7219_data = 0;
		}
		max7219_clk = 1;
	}
	//max7219_clk = 0;
	//envio del dato
	for(var_x=0;var_x<8;var_x++){
		max7219_clk = 0;
		if(dato & (1<<(7-var_x))){
			max7219_data = 1;
		}
		else{
			max7219_data = 0;
		}
		max7219_clk = 1;
	}
	max7219_cs = 1;
}