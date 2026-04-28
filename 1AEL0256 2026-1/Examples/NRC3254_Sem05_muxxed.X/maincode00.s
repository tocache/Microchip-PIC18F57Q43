    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upeceno, class=CODE, reloc=2, abs
upeceno:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf del modulo de oscilador
    movlb 0H
    movlw 59H
    movwf OSCCON1, 1	    ;NOSC LFINTOSC NDIV 1:512
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1	    ;HFINTOSC y LFINTOSC enabled
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	    ;RD6 al RD0 como salidas
    movwf ANSELD, 1	    ;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	    ;RB3 al RB0 como salidas
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    ;cond inicio
    clrf LATB, 1	    ;todos los habilitadores en 0

inicio:
    movlw 73H
    movwf LATD, 1
    bsf LATB, 0, 1
    call nopes
    bcf LATB, 0, 1
    movlw 5FH
    movwf LATD, 1
    bsf LATB, 1, 1
    call nopes
    bcf LATB, 1, 1
    movlw 6DH
    movwf LATD, 1
    bsf LATB, 2, 1
    call nopes
    bcf LATB, 2, 1
    movlw 7BH
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
   
    end upeceno
   
    


