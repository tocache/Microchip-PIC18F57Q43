    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000080H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 3H
    movlw 80H
    movwf T0CON0, 1	;Timer0 enabled, POSTSCALER 1:1
    movlw 4BH
    movwf T0CON1, 1	;FOSC/4, PRESCALER 1:2048
    movlw 244
    movwf TMR0H, 1	;Valor de referencia del comparador
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD) como digital

inicio:
    btfss PIR3, 7, 1	;Pregunto si TMR0IF=1
    bra $-2		;falso, vuelve a preguntar
    btg LATD, 0, 1	;complemento a RD0
    bcf PIR3, 7, 1	;bajamos bandera TMR0IF
    bra inicio
    
    end upcino