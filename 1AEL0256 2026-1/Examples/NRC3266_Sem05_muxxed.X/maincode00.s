    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT ARGH, class=CODE, reloc=2, abs
ARGH:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf modulo oscilador
    movlb 0H
    movlw 59H
    movwf OSCCON1, 1	    ;NOSC=LFINTOSC, NDIV=1:512
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1	    ;LFINTOSC HFINTOSC enabled
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1    
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    movlw 0FCH
    movwf ANSELF, 1
    movlw 03H
    movwf WPUF, 1
    
inicio:    
    movlw 6FH
    movwf LATD, 1
    bsf LATB, 0, 1
    call micro_delay
    bcf LATB, 0, 1
    movlw 5FH
    movwf LATD, 1
    bsf LATB, 1, 1
    call micro_delay
    bcf LATB, 1, 1
    movlw 78H
    movwf LATD, 1
    bsf LATB, 2, 1
    call micro_delay
    bcf LATB, 2, 1
    movlw 5CH
    movwf LATD, 1
    bsf LATB, 3, 1
    call micro_delay
    bcf LATB, 3, 1
    bra inicio

micro_delay:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
;6FH?
;5FH?
;78H?
;5CH
    end ARGH