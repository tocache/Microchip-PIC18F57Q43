#include "LIB_DHT.h"

void DHT_Start(unsigned char modelo){
    if(modelo == DHT11){
        TRISBbits.TRISB3 = 0;      //Puerto RB3 como salida
        ANSELBbits.ANSELB3 = 0;
        LATBbits.LATB3 = 0;       //Mandamos cero
        __delay_ms(18);         //Esperamos 18 milisegundo
        LATBbits.LATB3 = 1;       //Mandamos uno
        __delay_us(40);         //Esperamos 40 microsegundos
        TRISBbits.TRISB3 = 1;      //Puerto como entrada
    }
    else if(modelo == DHT22){
        TRISBbits.TRISB3 = 0;      //Puerto RB3 como salida
        ANSELBbits.ANSELB3 = 0;
        LATBbits.LATB3 = 0;       //Mandamos cero
        __delay_ms(1);         //Esperamos 1 milisegundo
        LATBbits.LATB3 = 1;       //Mandamos uno
        __delay_us(40);         //Esperamos 40 microsegundos
        TRISBbits.TRISB3 = 1;      //Puerto como entrada
    }
}

void DHT_Check(unsigned char modelo){
    unsigned char temp_x;
    if(modelo == DHT11){
        temp_x = 0;
        while((PORTBbits.RB3 == 1) && temp_x < 100){
            temp_x++;
        }
        __delay_us(80);
        temp_x = 0;
        while((PORTBbits.RB3 == 0) && temp_x < 100){
            temp_x++;
        }
        __delay_us(80);
        temp_x = 0;
        while((PORTBbits.RB3 == 1) && temp_x < 100){
            temp_x++;
        }
    }
    else if(modelo == DHT22){
        temp_x = 0;
        while((PORTBbits.RB3 == 1) && temp_x < 100){
            temp_x++;
        }
        __delay_us(80);
        temp_x = 0;
        while((PORTBbits.RB3 == 0) && temp_x < 100){
            temp_x++;
        }
        __delay_us(80);
        temp_x = 0;
        while((PORTBbits.RB3 == 1) && temp_x < 100){
            temp_x++;
        } 
    }        
}

unsigned char DHT_Read(unsigned char modelo){
    unsigned char x = 0, data = 0;
    unsigned char temp_x;
    if(modelo == DHT11){
        for(x=0;x<8;x++){
            temp_x = 0;
            while((PORTBbits.RB3 == 0) && temp_x < 100){
                temp_x++;
            }
            __delay_us(35);
            if(PORTBbits.RB3){
                data = ((data<<1) | 1);
            }
            else{
                data = (data<<1);
            }
            temp_x = 0;
            while((PORTBbits.RB3 == 1) && temp_x < 100){
                temp_x++;
            }
        }
    }
    else if(modelo == DHT22){
        for(x=0;x<8;x++){
            temp_x = 0;
            while((PORTBbits.RB3 == 0) && temp_x < 100){
                temp_x++;
            }
            __delay_us(35);
            if(PORTBbits.RB3){
                data = ((data<<1) | 1);
            }
            else{
                data = (data<<1);
            }
            temp_x = 0;
            while((PORTBbits.RB3 == 1) && temp_x < 100){
                temp_x++;
            }
        }        
    }
    return data;
}

unsigned int DHT_GetTemp(unsigned char modelo){
    unsigned char RH_Ent, RH_Dec, Temp_Ent, Temp_Dec, Chksum;
    unsigned int valor_dht=0;
    DHT_Start(modelo);
    DHT_Check(modelo);
    RH_Ent = DHT_Read(modelo);
    RH_Dec = DHT_Read(modelo);
    Temp_Ent = DHT_Read(modelo);
    Temp_Dec = DHT_Read(modelo);
    Chksum = DHT_Read(modelo); 
    if(modelo == DHT11){
        return(valor_dht + Temp_Ent);
    }
    else if(modelo == DHT22){
        valor_dht = (Temp_Ent << 8) | Temp_Dec;
        return(valor_dht);
    }
}

unsigned int DHT_GetHumid(unsigned char modelo){
    unsigned char RH_Ent, RH_Dec, Temp_Ent, Temp_Dec, Chksum;
    unsigned int valor_dht=0;
    DHT_Start(modelo);
    DHT_Check(modelo);
    RH_Ent = DHT_Read(modelo);
    RH_Dec = DHT_Read(modelo);
    Temp_Ent = DHT_Read(modelo);
    Temp_Dec = DHT_Read(modelo);
    Chksum = DHT_Read(modelo); 
    if(modelo == DHT11){
        return(valor_dht + RH_Ent);
    }
    else if(modelo == DHT22){
        valor_dht = (RH_Ent << 8) | RH_Dec;
        return(valor_dht);
    }
}
