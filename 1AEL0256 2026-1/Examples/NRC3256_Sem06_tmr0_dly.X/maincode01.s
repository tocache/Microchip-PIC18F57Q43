    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT yaps, class=CODE, reloc=2, abs
yaps:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf mod osc
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf TMR0
    movlb 3H
    movlw 90H
    movwf T0CON0, 1
    movlw 0A1H
    movwf T0CON1, 1
    ;conf E/S
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1

inicio:
    movlb 3H
    movlw 3CH
    movwf TMR0H, 1
    movlw 0B0H
    movwf TMR0L, 1	;cta inicial 15536 en TMR0
    movlb 4H
    btfss PIR3, 7, 1	;preg si TMR0 se desbordo
    bra $-2
    bcf PIR3, 7, 1	;bajo bandera TMR0IF
    btg LATC, 0, 1	;basculo RC0
    bra inicio

    end yaps


