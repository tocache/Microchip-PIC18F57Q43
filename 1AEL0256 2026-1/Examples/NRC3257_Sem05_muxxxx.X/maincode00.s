    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT chesss, class=CODE, reloc=2, abs
chesss:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf mod osc
    movlb 0H
    movlw 50H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    movlw 0FCH
    movwf TRISF, 1
    movlw 03H
    movwf WPUF, 1
    ;cond iniciales
    clrf LATB, 1	    ;habilitadores G1, G2, G3, G4 apagados
    
inicio:
    movlw 58H
    movwf LATD, 1
    bsf LATB, 0, 1
    call micro_delay
    bcf LATB, 0, 1
    movlw 74H
    movwf LATD, 1
    bsf LATB, 1, 1
    call micro_delay
    bcf LATB, 1, 1
    movlw 5FH
    movwf LATD, 1
    bsf LATB, 2, 1
    call micro_delay
    bcf LATB, 2, 1
    movlw 1CH
    movwf LATD, 1
    bsf LATB, 3, 1
    call micro_delay
    bcf LATB, 3, 1
    bra inicio
    
micro_delay:
    movlb 5H
    movlw 5
    movwf 500H
    nop
    decfsz 500H, 1, 1
    bra $-4
    movlb 4H
    return

    end chesss
    