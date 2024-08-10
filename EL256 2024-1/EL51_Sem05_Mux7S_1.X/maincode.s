    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:    
    movlb 0H
    movlw 60H		;1:512
    movwf OSCCON1, 1
    movlw 00H
    movwf OSCFRQ, 1	;1MHz
    movlw 40H
    movwf OSCEN, 1	;2Khz al CPU
    movlb 4H
    clrf TRISD, 1
    clrf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    clrf LATB, 1
    
inicio:
    movlw 76H
    movwf LATD, 1
    bsf LATB, 0, 1
    call nopx16
    bcf LATB, 0, 1
    movlw 3FH
    movwf LATD, 1
    bsf LATB, 1, 1
    call nopx16
    bcf LATB, 1, 1
    movlw 38H
    movwf LATD, 1
    bsf LATB, 2, 1
    call nopx16
    bcf LATB, 2, 1
    movlw 77H
    movwf LATD, 1
    bsf LATB, 3, 1
    call nopx16
    bcf LATB, 3, 1
    bra inicio
    
nopx16:
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