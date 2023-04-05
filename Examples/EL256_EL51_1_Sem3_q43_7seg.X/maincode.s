    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro

    ORG 000020H
configuro:
    movlb 0
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    bsf OSCEN, 6
    movlb 4
    clrf TRISD
    clrf ANSELD
    ;movlw 0FFH
    movlw 255D
    ;movlw 11111111B
    movwf TRISB
    clrf ANSELB
    movlw 0FH
    movwf WPUB
    
inicio:
    btfsc PORTB, 0
    goto otro1
    movlw 01110110B
    movwf LATD
    bra inicio
otro1:
    btfsc PORTB, 1
    goto otro2
    movlw 00111111B
    movwf LATD
    bra inicio
otro2:
    btfsc PORTB, 2
    goto otro3
    movlw 00111000B
    movwf LATD
    bra inicio
otro3:    
    btfsc PORTB, 3
    goto otro4
    movlw 01110111B
    movwf LATD
    bra inicio
otro4:    
    clrf LATD
    bra inicio
    end upcino




