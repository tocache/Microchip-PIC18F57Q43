//Librería LIB_UART desarrollada por Kalun Lau
//Curso de Microcontroladores
//Universidad Peruana de Ciencias Aplicadas
//Ultima edicion 10/06/2024

//Changelog:
//10/06/2024: Se esta considerando el uso del U1
//como períferico a emplearse en la comunicacion serial.
//La velocidad de comunicacion establecida es 9600
//La frecuencia de trabajo es de 32MHz
//Tener en cuenta que para la recepcion de datos se esta
//empleando interrupciones del USART para recepcion

//Instrucciones para usar la librería
//1.Llamar a U1_INIT() para configurar el UART U1
//2.Para la parte de recepcion deberan de habilitar
//la funcion de interrupcion en el codigo principal

#include <xc.h>
#include <string.h>
#include "LIB_UART.h"

void U1_INIT(unsigned int velocidad){
    //configuracion del UART
    U1BRGH = (velocidad >>8) & 0x00FF; //revisar defines en LIB_UART.h
    U1BRGL = velocidad & 0x00FF;  //revisar defines en LIB_UART.h           
    U1CON0 = 0x30;          //TX enabled, RX enabled
    U1CON1 = 0x80;
    U1CON2 = 0x00;
    RF0PPS = 0x20;           //RF0 esta conectado a UART1TX
    U1RXPPS = 0x29;             //RF1 esta conectado a UART1RX
    //configuracion de las interrupciones
    //PIE4bits.U1RXIE = 1;
    //PIR4bits.U1RXIF = 0;
    //INTCON0bits.GIE = 1;
}

/*funcion para enviar un dato de 8 bits*/
void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

/*funcion para enviar una cadena de caracteres*/
void U1_STRING_SEND(const char *cadena)
{
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
}

/*funcion para enviar una cadena de caracteres
  con salto de linea al final*/
void U1_STRING_SENDLN(const char *cadena)
{
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

/*funcion para visualizar una variable de 8 bits en formato decimal*/
void U1_VAR_CHAR(unsigned char numero, unsigned char n_digitos){
    unsigned char centena, decena, unidad;  //variables de funcion convierte
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 2:
            U1_BYTE_SEND(decena+0x30);
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 3:
            U1_BYTE_SEND(centena+0x30);
            U1_BYTE_SEND(decena+0x30);
            U1_BYTE_SEND(unidad+0x30);
            break;
    }
}

/*funcion para visualizar una variable de 16 bits en formato decimal*/
void U1_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto){
    unsigned char d_millar, millar, centena, decena, unidad;  //variables de funcion convierte
    d_millar = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena =  (numero % 100) / 10;
    unidad = numero % 10;
    switch(n_digitos){
        case 1:
            U1_BYTE_SEND(unidad+0x30);
            break;
        case 2:
            if(punto == 0){
                U1_BYTE_SEND(decena+0x30);
                U1_BYTE_SEND(unidad+0x30);
            }
            else if(punto == 1){
                U1_BYTE_SEND(decena+0x30);
                U1_BYTE_SEND('.');
                U1_BYTE_SEND(unidad+0x30);
            }
            break;
        case 3:
            switch(punto){
                case 0:
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 1:
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 2:
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
            }
            break;
        case 4:
            switch(punto){
                case 0:
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 1:
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 2:
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 3:
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
            }
            break;
        case 5:
            switch(punto){
                case 0:
                    U1_BYTE_SEND(d_millar+0x30);
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 1:
                    U1_BYTE_SEND(d_millar+0x30);
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 2:
                    U1_BYTE_SEND(d_millar+0x30);
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 3:
                    U1_BYTE_SEND(d_millar+0x30);
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
                case 4:
                    U1_BYTE_SEND(d_millar+0x30);
                    U1_BYTE_SEND('.');
                    U1_BYTE_SEND(millar+0x30);
                    U1_BYTE_SEND(centena+0x30);
                    U1_BYTE_SEND(decena+0x30);
                    U1_BYTE_SEND(unidad+0x30);
                    break;
            }
            break;
    }
}

void U1_NEWLINE(void){
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

//funcion de ejemplo para la recepcion de datos, debera de ser
//colocado en el archivo fuente
//el dato recepcionado se encuentra en el registro U1RXB
/*void __interrupt(irq(IRQ_U1RX)) U1RX_ISR(void){
    PIR4bits.U1RXIF = 0;
    switch(U1RXB){
        case '1':
            LATCbits.LATC0 = 1;
            break;
        case '2':
            LATCbits.LATC0 = 0;
            break;
        case '3':
            LATCbits.LATC1 = 1;
            break;
        case '4':
            LATCbits.LATC1 = 0;
            break;
    }
}
*/

