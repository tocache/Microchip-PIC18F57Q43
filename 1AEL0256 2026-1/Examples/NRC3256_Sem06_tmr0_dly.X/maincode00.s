    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT yaps, class=CODE, reloc=2, abs
yaps:
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
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1

inicio:
    bsf LATC, 0, 1
    call DLY_200ms
    bcf LATC, 0, 1
    call DLY_200ms
    bra inicio
    
DLY_200ms:
RegX EQU 500H
RegY EQU 501H
RegZ EQU 502H
    movlb 5H
    movlw 50
    movwf RegX, 1
ret_RegX:
    movlw 50
    movwf RegY, 1
ret_RegY:
    movlw 20
    movwf RegZ, 1
ret_RegZ:
    nop
    decfsz RegZ, 1, 1
    bra ret_RegZ
    decfsz RegY, 1, 1
    bra ret_RegY
    decfsz RegX, 1, 1
    bra ret_RegX
    movlb 4H
    return
    end yaps