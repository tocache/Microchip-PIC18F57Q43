#ifndef LCD_LIB_H_
#define	LCD_LIB_H_

#define OON  0
#define OFF 1
#define RS  LATDbits.LATD0
#define RW  LATDbits.LATD1
#define E   LATDbits.LATD2
#define _XTAL_FREQ 32000000UL

void POS_CURSOR(unsigned char fila,unsigned char columna);
void DISPLAY_ONOFF(unsigned char estado);
void CURSOR_HOME(void);
void CURSOR_ONOFF(unsigned char estado);
void ENVIA_CHAR(unsigned char dato);
void BORRAR_LCD(void);
void LCD_CONFIG(void);
void ENVIA_NIBBLE(unsigned char dato);
void ENVIA_LCD_CMD(unsigned char dato);
void LEER_LCD(void);
void BLINK_CURSOR(unsigned char val);
void GENERACARACTER(const unsigned char *vector,unsigned char pos);
void ESCRIBE_MENSAJE(const char *cadena,unsigned char tam);
void ESCRIBE_MENSAJE2(const char *cadena);
void CURSOR_SHIFTLEFT(void);
void CURSOR_SHIFTRIGHT(void);
void DISPLAY_SHIFTLEFT(void);
void DISPLAY_SHIFTRIGHT(void);
void LCD_INIT(void);
void LCD_ESCRIBE_VAR_CHAR(unsigned char numero, unsigned char n_digitos);
void LCD_ESCRIBE_VAR_INT(unsigned int numero, unsigned char n_digitos);
void LCD_CHAR_GRADO(void);
void LCD_VARCHAR_BITS(unsigned char dato);

#endif	/* XC_HEADER_TEMPLATE_H */