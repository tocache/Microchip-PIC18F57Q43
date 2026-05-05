    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT labubu, class=CODE, reloc=2, abs
labubu:
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
    ;conf PPS
    movlb 2H
    movlw 39H
    movwf RF0PPS, 1
    ;conf Timer0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1
    movlw 0AAH
    movwf T0CON1, 1
    ;conf E/S
    movlb 4H
    movlw 0FCH
    movwf TRISF, 1
    movwf ANSELF, 1
    
inicio:
    bsf LATF, 1, 1
    call dly_250ms
    bcf LATF, 1, 1
    call dly_250ms
    bra inicio
    
dly_250ms:
RegX EQU 500H
RegY EQU 501H
RegZ EQU 502H
    movlb 5H
    movlw 45
    movwf RegX, 1
retornoX:
    movlw 45
    movwf RegY, 1
retornoY:
    movlw 24
    movwf RegZ, 1
    nop
    nop
    decfsz RegZ, 1, 1
    bra $-06H
    decfsz RegY, 1, 1
    bra retornoY
    decfsz RegX, 1, 1
    bra retornoX
    movlb 4H
    return
    
    end labubu


