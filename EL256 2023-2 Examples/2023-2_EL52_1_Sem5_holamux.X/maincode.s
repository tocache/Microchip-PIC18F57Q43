    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE,reloc=2, abs
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
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6-RD0 como salidas
    movwf ANSELD, 1	;RD6-RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3-RB0 como salidas
    movwf ANSELB, 1	;RB3-RB0 como digitales
    clrf LATB, 1	;Habilitadores en cero (cond inicial)
    
inicio:
    movlw 76H
    movwf LATD, 1
    bsf LATB, 0, 1
    call nopes
    bcf LATB, 0, 1
    movlw 3FH
    movwf LATD, 1
    bsf LATB, 1, 1
    call nopes
    bcf LATB, 1, 1
    movlw 38H
    movwf LATD, 1
    bsf LATB, 2, 1
    call nopes
    bcf LATB, 2, 1
    movlw 77H
    movwf LATD, 1
    bsf LATB, 3, 1
    call nopes
    bcf LATB, 3, 1
    bra inicio
    
nopes:
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


