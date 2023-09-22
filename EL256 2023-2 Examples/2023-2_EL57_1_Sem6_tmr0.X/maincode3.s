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
    movwf T0CON0, 1	;TMR0 enabled, 16bit, postscaler 1:1
    movlw 40H		
    movwf T0CON1, 1	;FOSC/4, prescaler 1:1, async
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital
    
inicio:
    movlb 4H
    bsf LATD, 0, 1	;RD0 a uno
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 38H
    movwf TMR0L, 1	;Precarga de cuenta 65036 a TMR0
    movlb 4H
otro:    
    btfss PIR3, 7, 1	;Pregunto si TMR0IF=1
    bra otro		;Aun no se levanta TMR0IF
    bcf PIR3, 7, 1	;Bajamos bandera TMR0IF
    bcf LATD, 0, 1	;RD0 a cero
    movlb 3H
    movlw 0FCH
    movwf TMR0H, 1
    movlw 0E0H
    movwf TMR0L, 1	;Precarga de cuenta 64736 a TMR0
    movlb 4H
otro2:    
    btfss PIR3, 7, 1	;Pregunto si TMR0IF=1
    bra otro2		;Aun no se levanta TMR0IF
    bcf PIR3, 7, 1	;Bajamos bandera TMR0IF    
    bra inicio
    
    end upcino







