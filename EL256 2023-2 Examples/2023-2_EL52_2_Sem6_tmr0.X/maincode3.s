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
    movlw 90H
    movwf T0CON0, 1	;Timer0 enabled, POSTSCALER 1:1
    movlw 40H
    movwf T0CON1, 1	;FOSC/4, PRESCALER 1:2048
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD) como digital

inicio:
    bsf LATD, 0, 1	;RD0=1
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1	
    movlw 38H
    movwf TMR0L, 1	;Carga de cuenta inicial 65336 en TMR0
    movlb 4H
    btfss PIR3, 7, 1	;Pregunto si TMR0IF=1
    bra $-2		;falso, vuelve a preguntar
    bcf PIR3, 7, 1	;bajamos bandera TMR0IF
    bcf LATD, 0, 1	;RD0=0
    movlb 3H
    movlw 0FCH
    movwf TMR0H, 1	
    movlw 0E0H
    movwf TMR0L, 1	;Carga de cuenta inicial 64736 en TMR0
    movlb 4H
    btfss PIR3, 7, 1	;Pregunto si TMR0IF=1
    bra $-2		;falso, vuelve a preguntar
    bcf PIR3, 7, 1	;bajamos bandera TMR0IF
    bra inicio
    end upcino





