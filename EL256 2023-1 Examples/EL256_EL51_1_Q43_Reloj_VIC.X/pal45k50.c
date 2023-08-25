

//en la configuracion:
void configuro(void){
GIE = 1;
CCP1IE = 1;
INT0IE = 1;
INT1IE = 1;
INT2IE = 1;
}

void __interrupt() ISRs(void){
    if (CCP1IF = 1){
        CCP1IF = 0;
        ...
    }
    else if (INT0IF = 1){
        INT0IF = 0;
        ...
    }
    else if (INT1IF = 1){
        INT1IF = 0;
        ...
    }
    else if (INT2IF = 1){
        INT2IF = 0;
        ...
    }
}

