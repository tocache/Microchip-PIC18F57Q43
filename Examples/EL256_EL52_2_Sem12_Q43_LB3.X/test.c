unsigned int tomamuestra_ADC(unsigned char canal){
    switch(canal){
        case 3:
            ADCON0 = 0x0D;
            break;
        case 5:
            ADCON0 = 0x15;
            break;
        case 6:
            ADCON0 = 0x19;
            break;
    }
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    return (ADRESH<<8) + ADRESL;
}