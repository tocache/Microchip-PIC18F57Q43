    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 001000H
mensaje:    DB 76H, 3FH, 38H, 77H    
;mensaje1: DB "HOLA"    
    
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    BANKSEL 0
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    movlw 40H
    movwf OSCEN
    BANKSEL 4
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL
    movlw 80H
    movwf TRISD
    movwf ANSELD
    movlw 0F0H
    movwf TRISB
    movwf ANSELB
    clrf LATB

inicio:    
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0
    call retardito
    bcf LATB, 0
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1
    call retardito
    bcf LATB, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2
    call retardito
    bcf LATB, 2
    TBLRD*
    movff TABLAT, LATD
    bsf LATB, 3
    call retardito
    bcf LATB, 3
    clrf TBLPTRL
    bra inicio
    
retardito:
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
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
    end upcino


