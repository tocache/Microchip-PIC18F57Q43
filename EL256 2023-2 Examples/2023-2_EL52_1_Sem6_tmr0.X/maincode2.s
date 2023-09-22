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
    movwf T0CON0, 1	;TMR0 enabled, postsc 1:1 modo 16bit
    movlw 40H
    movwf T0CON1, 1	;FOSC/4 Presc 1:1
    movlw 0FEH
    movwf TMR0H, 1
    movlw 0CH
    movwf TMR0L, 1	;cuenta inicial de 65036 al arranque
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital
    
inicio:    
    btfss PIR3, 7, 1	;pregunto si TMR0IF=1
    bra inicio		;falso regreso a preguntar
    btg LATD, 0, 1	;verdad, aplico complemento a RD0
    bcf PIR3, 7, 1	;bajo la bandera TMR0IF
    movlb 3H
    movlw 0FEH
    movwf TMR0H, 1
    movlw 0CH
    movwf TMR0L, 1
    movlb 4H
    bra inicio
    
    end upcino



