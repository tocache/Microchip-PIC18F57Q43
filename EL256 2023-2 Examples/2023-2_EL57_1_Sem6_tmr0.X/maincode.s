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
    movwf T0CON0, 1	;TMR0 enabled, 8bit, postscaler 1:1
    movlw 4BH		
    movwf T0CON1, 1	;FOSC/4, prescaler 1:2048, async
    setf TMR0H, 1   	;Valor de comparación 255 para el TMR0 en modo 8 bit
    movlb 4H
    bcf TRISD, 0, 1
    bcf ANSELD, 0, 1
    
inicio:
    btfss PIR3, 7, 1	;Pregunto si TMR0IF=1
    bra inicio		;Aun no se levanta TMR0IF
    btg LATD, 0, 1	;Complemento a RD0
    bcf PIR3, 7, 1	;Bajamos bandera TMR0IF
    bra inicio
    
    end upcino

