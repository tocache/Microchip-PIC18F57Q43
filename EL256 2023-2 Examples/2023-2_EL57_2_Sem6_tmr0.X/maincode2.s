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
    movlw 90H
    movwf T0CON0, 1	;TMR0 enabled, 16bit mode, postscaler 1:1
    movlw 40H
    movwf T0CON1, 1	;FOSC/4, async, prescaler 1:1
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital

inicio:
    btfss PIR3, 7, 1	;Pregunto si hubo match en TMR0, TMR0IF=1
    bra inicio
    btg LATD, 0, 1	;Complementamos RD0
    bcf PIR3, 7, 1	;Bajamos la bandera TMR0 IF
    movlb 3H
    movlw 0FEH
    movwf TMR0H, 1
    movlw 0CH
    movwf TMR0L, 1
    movlb 4H
    bra inicio
    
    end upcino



