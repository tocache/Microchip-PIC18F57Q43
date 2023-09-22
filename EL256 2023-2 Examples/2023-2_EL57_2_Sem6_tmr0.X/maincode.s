    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
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
    movwf T0CON0, 1	;TMR0 enabled, 8bit mode, postscaler 1:1
    movlw 4BH
    movwf T0CON1, 1	;FOSC/4, async, prescaler 1:2048
    movlw 245
    movwf TMR0H		;Valor de comparación 245
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital

inicio:
    btfss PIR3, 7, 1	;Pregunto si hubo match en TMR0, TMR0IF=1
    bra inicio
    btg LATD, 0, 1	;Complementamos RD0
    bcf PIR3, 7, 1	;Bajamos la bandera TMR0 IF
    bra inicio
    
    end upcino
