#ifndef U1SERIAL_LIB_H_
#define	U1SERIAL_LIB_H_

#define _XTAL_FREQ 32000000UL
#define BAUD9600 207
#define BAUD19200 103
#define BAUD38400 51

void U1_INIT(unsigned char baudios);
void U1_DATA_SEND(unsigned char dato);
void U1_STRING_SEND(const char *cadena);
void U1_NEWLINE(void);
void U1_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos);
void U1_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos);

#endif	/* XC_HEADER_TEMPLATE_H */