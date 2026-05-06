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
    ;conf tmr0
    movlb 3H
    movlw 90H
    movwf T0CON0, 1
    movlw 0A2H
    movwf T0CON1, 1
    ;conf e/s
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    
inicio:
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1
    btg LATC, 0, 1
    movlb 3H
    movlw 3CH
    movwf TMR0H, 1
    movlw 0B0H
    movwf TMR0L, 1
    movlb 4H
    bra inicio
    
    end yaps



