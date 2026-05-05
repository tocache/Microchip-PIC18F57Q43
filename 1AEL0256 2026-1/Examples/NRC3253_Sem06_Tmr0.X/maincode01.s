    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT papadeus, class=CODE, reloc=2, abs
papadeus:
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
    movlw 60H
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
    movlw 183
    movwf TMR0H, 1
    ;conf E/S
    movlb 4H
    movlw 0FCH
    movwf TRISF, 1
    movwf ANSELF, 1
    
inicio:
    bsf LATF, 1, 1
    call del_250ms
    bcf LATF, 1, 1
    call del_250ms
    bra inicio

del_250ms:	;que en realidad es 251.29ms segun stopwatch
Reg_X EQU 500H
Reg_Y EQU 501H
Reg_Z EQU 502H 
    movlb 5H
    movlw 45
    movwf Reg_Z, 1
ret_Y:
    movlw 45
    movwf Reg_Y, 1
ret_X:
    movlw 30
    movwf Reg_X, 1
    nop
    decfsz Reg_X, 1, 1
    bra $-4
    decfsz Reg_Y, 1, 1
    bra ret_X
    decfsz Reg_Z, 1, 1
    bra ret_Y
    movlb 4H
    return
    
    end papadeus
    





