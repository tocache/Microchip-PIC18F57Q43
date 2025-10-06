#ifndef LIB_UART_H_
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

#define	LIB_UART_H_
#define _XTAL_FREQ 32000000UL

#define BAUD_4800 416   //No va a funcionar
#define BAUD_9600 207
#define BAUD_19200 103
#define BAUD_57600 34
#define BAUD_115200 16

/*Función para inicializar el periférico UART U1
 Opciones:  BAUD_4800,
            BAUD_9600,
            BAUD_19200,
            BAUD_57600,
            BAUD_115200*/
void U1_INIT(unsigned int velocidad);

/*Funcion para enviar un dato de 8 bits*/
void U1_BYTE_SEND(unsigned char dato);

/*Funcion para enviar una cadena de caracteres*/
void U1_STRING_SEND(const char *cadena);

/*Funcion para visualizar una variable de 8 bits en formato decimal*/
void U1_VAR_CHAR(unsigned char numero, unsigned char n_digitos);

/*Funcion para visualizar una variable de 16 bits en formato decimal*/
void U1_VAR_INT(unsigned int numero, unsigned char n_digitos, unsigned char punto);

/*Funcion para irse una linea abajo en el terminal*/
void U1_NEWLINE(void);

#endif	/* XC_HEADER_TEMPLATE_H */