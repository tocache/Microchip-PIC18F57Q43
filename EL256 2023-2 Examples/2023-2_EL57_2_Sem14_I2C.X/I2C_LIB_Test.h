// definir los pines del PCF8574 y sus pesos
#define P0 0b00000001   //1
#define P1 0b00000010   //2
#define P2 0b00000100   //4
#define P3 0b00001000   //8
#define P4 0b00010000   //16
#define P5 0b00100000   //32
#define P6 0b01000000   //64
#define P7 0b10000000   //128

//conexiones y utilidades del PCF8574
#define PCF8574_ADDR 0x20
#define I2C_LCD_BKL P3
#define I2C_LCD_RS P0
#define I2C_LCD_RW P1
#define I2C_LCD_E P2
#define I2C_LCD_D4 P4
#define I2C_LCD_D5 P5
#define I2C_LCD_D6 P6
#define I2C_LCD_D7 P7

