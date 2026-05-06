    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT yaps, class=CODE, reloc=2, abs
yaps:
    ORG 000000H
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
    ;conf e/s
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    
inicio:
    bsf LATC, 0, 1
    call dly_400ms	;retardo muy cercano a 400ms
    bcf LATC, 0, 1
    call dly_400ms
    bra inicio
    
dly_400ms:
RegX EQU 500H
RegY EQU 501H
RegZ EQU 502H 
    movlb 5H
    movlw 50
    movwf RegX, 1
retornoX:    
    movlw 50
    movwf RegY, 1
retornoY:    
    movlw 39
    movwf RegZ, 1
    nop
    decfsz RegZ, 1, 1
    bra $-4
    decfsz RegY, 1, 1
    bra retornoY
    decfsz RegX, 1, 1
    bra retornoX
    movlb 4H
    return
    
    end yaps
