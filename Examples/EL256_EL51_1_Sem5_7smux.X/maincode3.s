    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
corredera EQU 500H    
    ORG 001000H
mensaje:    DB 00H, 00H, 00H, 00H, 76H, 3FH, 38H, 77H, 00H, 00H, 00H
    
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    movlb 0
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    movlw 40H
    movwf OSCEN
    movlb 3
    movlw 90H
    movwf T0CON0
    movlw 64H
    movwf T0CON1
    movlb 4
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
    clrf corredera
    
inicio:    
    btfss PIR3, 7
    bra pal_mux
    movlw 7
    cpfseq corredera
    bra no_siete
    clrf corredera
    bcf PIR3, 7
    bra pal_mux
no_siete:
    incf corredera, 1
    bcf PIR3, 7
pal_mux:
    movff corredera, TBLPTRL
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





