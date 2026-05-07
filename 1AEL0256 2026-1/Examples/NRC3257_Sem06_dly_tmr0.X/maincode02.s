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
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISF, 1
    movwf ANSELF, 1
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 08H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    movlb 5H
    clrf 500H
    movlb 4H
    
inicio:
    btfss PIR3, 7, 1
    bra noes
    bcf PIR3, 7, 1
    btg LATC, 0, 1
noes:    
    btfss PORTC, 0, 1
    bra primero
    bra segundo
primero:
    clrf TBLPTRL, 1
    bra siguiente
segundo:
    movlw 04H
    movwf TBLPTRL, 1
siguiente:    
    call multiplex
    bra inicio
    
multiplex:
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 0, 1
    call nops
    bcf LATF, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 1, 1
    call nops
    bcf LATF, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 2, 1
    call nops
    bcf LATF, 2, 1
    TBLRD*
    movff TABLAT, LATD
    bsf LATF, 3, 1
    call nops
    bcf LATF, 3, 1
    return
    
nops:
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
    
    ORG 000800H
msg1:	DB 5CH, 63H, 5CH, 63H
msg2:	DB 63H, 5CH, 63H, 5CH
    end argh





