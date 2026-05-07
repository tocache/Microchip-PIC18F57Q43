    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT argh, class=CODE, reloc=2, abs
argh:
    ORG 0000000H
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
    movlw 80H
    movwf T0CON0, 1
    movlw 6DH
    movwf T0CON1, 1
    movlw 98
    movwf TMR0H, 1
    ;conf E/S
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    
inicio:
    btfss PIR3, 7, 1
    bra inicio
    bcf PIR3, 7, 1
    btg LATC, 0, 1
    bra inicio
    end argh


