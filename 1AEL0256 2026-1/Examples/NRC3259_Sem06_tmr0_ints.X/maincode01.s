    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT viernes, class=CODE, reloc=2, abs
viernes:
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
    movwf T0CON0, 1
    movlw 65H
    movwf T0CON1, 1
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    
inicio:
    movlb 5H
    btfss 501H, 0, 1
    bra lento
    bra rapido
lento:    
    movlb 3H
    movlw 6DH
    movwf TMR0H, 1
    movlw 84H
    movwf TMR0L, 1
    bra salto
rapido:    
    movlw 0B6H
    movwf TMR0H, 1
    movlw 0C2H
    movwf TMR0L, 1    
    bra salto
salto:    
    movlb 4H
    btfss PIR3, 7, 1
    bra salto
    bcf PIR3, 7, 1
    btg LATC, 0, 1
    movlb 5H
    incf 500H, 1, 1
    movlw 10
    cpfseq 500H, 1
    bra nocambio
    bra sicambio
nocambio:
    bra final
sicambio:
    clrf 500H, 1
    btg 501H, 0, 1
    bra final
final:    
    bra inicio
    end viernes




