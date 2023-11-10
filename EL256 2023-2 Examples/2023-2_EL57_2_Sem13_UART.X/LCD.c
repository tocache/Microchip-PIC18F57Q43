#include <xc.h>
#include "LCD.h"
#include <string.h>

void POS_CURSOR(unsigned char fila,unsigned char columna)
{
	if(fila == 1)
	{
		ENVIA_LCD_CMD(0x80+columna);
	}
	else if(fila == 2)
	{
		ENVIA_LCD_CMD(0xC0+columna);
	}
	else if(fila == 3)
	{
		ENVIA_LCD_CMD(0x94+columna);
	}
	else if(fila == 4)
	{
		ENVIA_LCD_CMD(0xD4+columna);
	}
}

void BLINK_CURSOR(unsigned char val)
{
	if(val == OFF) ENVIA_LCD_CMD(0x0E);
	if(val == OON ) ENVIA_LCD_CMD(0x0F);
}

void DISPLAY_ONOFF(unsigned char estado)
{
	if(estado == OON)  ENVIA_LCD_CMD(0x0F);
	if(estado == OFF) ENVIA_LCD_CMD(0x08);
}

void CURSOR_HOME(void)
{
	ENVIA_LCD_CMD(0x02);
}

void CURSOR_SHIFTLEFT(void)
{
	ENVIA_LCD_CMD(0x10);
}

void CURSOR_SHIFTRIGHT(void)
{
	ENVIA_LCD_CMD(0x14);
}

void DISPLAY_SHIFTLEFT(void)
{
	ENVIA_LCD_CMD(0x18);
}

void DISPLAY_SHIFTRIGHT(void)
{
	ENVIA_LCD_CMD(0x1C);
}

void CURSOR_ONOFF(unsigned char estado)
{	
	if(estado == OON)	ENVIA_LCD_CMD(0x0E);
	if(estado == OFF)	ENVIA_LCD_CMD(0x0C);
}

void ESCRIBE_MENSAJE(const char *cadena,unsigned char tam)
{
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		ENVIA_CHAR(cadena[i]);
	}
}

void ESCRIBE_MENSAJE2(const char *cadena)
{
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		ENVIA_CHAR(cadena[i]);
	}
}

void ENVIA_CHAR(unsigned char dato)
{
	unsigned char aux;
	RS = 1;
	LEER_LCD();
	TRISD = 0x00;
    __delay_us(100);
	RW = 0;
	E = 0;
	RS = 1;
	aux = dato & 0xF0;
	ENVIA_NIBBLE(aux);
	aux = dato << 4;
	ENVIA_NIBBLE(aux);	
}

void BORRAR_LCD(void)
{
	ENVIA_LCD_CMD(0x01);
}

void LCD_CONFIG(void)
{
	RS = 0;
	RW = 0;
	ENVIA_NIBBLE(0x30);
    __delay_ms(2);
	ENVIA_NIBBLE(0x30);
    __delay_us(100);
    ENVIA_NIBBLE(0x30);
	ENVIA_NIBBLE(0x20);
	ENVIA_LCD_CMD(0x01);
	ENVIA_LCD_CMD(0x28);
	ENVIA_LCD_CMD(0x0F);
	ENVIA_LCD_CMD(0x06);
	ENVIA_LCD_CMD(0x01);
}

void ENVIA_NIBBLE(unsigned char dato)
{
	LATD &= 0x0F;
	dato &= 0xF0;
	LATD|= dato;
	E = 1;
    __delay_us(100);
	E = 0;
}

void ENVIA_LCD_CMD(unsigned char dato)
{
	unsigned char aux;
	RS = 0;
	LEER_LCD();
	TRISD = 0b00000000;
    __delay_us(100);
    RW = 0;
	E = 0;
	RS = 0;
	aux = dato & 0xF0;
	ENVIA_NIBBLE(aux);
	aux = dato<<4;
	ENVIA_NIBBLE(aux);
}

void LEER_LCD(void)
{
	unsigned char aux;	
	TRISD = 0xF8;
	RS = 0;
	RW = 1;
	E = 1;
    __delay_us(100);
	aux = PORTD;
	E = 0;
    __delay_us(100);
	E = 1;
    __delay_us(100);
	E = 0;
	aux = aux & 0x80;
	while(aux == 0x80)
        {
            E = 1;
            __delay_us(100);
            aux = PORTD;
            E = 0;
            __delay_us(100);
            E = 1;
            __delay_us(100);
            E = 0;
            aux = aux & 0x80;
	}
}

void GENERACARACTER(const unsigned char *vector,unsigned char pos)
{
	unsigned char i;
	ENVIA_LCD_CMD(0x40+8*pos);//Dirección de la CGRAM +
	for(i=0;i<8;i++)			 //offset de posición de caracter	
	{
		ENVIA_CHAR(vector[i]);
	}
	ENVIA_LCD_CMD(0x80);	//Dirección de la DDRAM
}

void LCD_INIT(void){
    TRISD = 0x00;
    ANSELD = 0x00;
    __delay_ms(15);
    LCD_CONFIG();
    __delay_ms(15);
    BORRAR_LCD();
    CURSOR_HOME();
    CURSOR_ONOFF(OFF);
}

void LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos){
    unsigned char centena, decena, unidad;  //variables de funcion convierte
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            ENVIA_CHAR(unidad+0x30);
            break;
        case 2:
            ENVIA_CHAR(decena+0x30);
            ENVIA_CHAR(unidad+0x30);
            break;
        case 3:
            ENVIA_CHAR(centena+0x30);
            ENVIA_CHAR(decena+0x30);
            ENVIA_CHAR(unidad+0x30);
            break;
    }
}

void LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos){
    unsigned char d_millar, millar, centena, decena, unidad;  //variables de funcion convierte
    d_millar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            ENVIA_CHAR(unidad+0x30);
            break;
        case 2:
            ENVIA_CHAR(decena+0x30);
            ENVIA_CHAR(unidad+0x30);
            break;
        case 3:
            ENVIA_CHAR(centena+0x30);
            ENVIA_CHAR(decena+0x30);
            ENVIA_CHAR(unidad+0x30);
            break;
        case 4:
            ENVIA_CHAR(millar+0x30);
            ENVIA_CHAR(centena+0x30);
            ENVIA_CHAR(decena+0x30);
            ENVIA_CHAR(unidad+0x30);
            break;
        case 5:
            ENVIA_CHAR(d_millar+0x30);
            ENVIA_CHAR(millar+0x30);
            ENVIA_CHAR(centena+0x30);
            ENVIA_CHAR(decena+0x30);
            ENVIA_CHAR(unidad+0x30);
            break;
    }
}

void LCD_CHAR_GRADO(void){
    ENVIA_CHAR(0xDF);
}

void LCD_VARCHAR_BITS(unsigned char dato){
    unsigned char x_var;
    for(x_var=0;x_var<8;x_var++){
        if (((dato >> (7 - x_var)) & 0x01) == 1){
            ENVIA_CHAR('1');
        }
        else{
            ENVIA_CHAR('0');
        }
    }
}