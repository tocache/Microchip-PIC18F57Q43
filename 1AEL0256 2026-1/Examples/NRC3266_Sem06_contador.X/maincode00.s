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
    ;conf PPS
    movlb 2H
    movlw 28H
    movwf T0CKIPPS, 1	    ;RF0 asignado a T0CKI
    ;conf tmr0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1
    movlw 30H
    movwf T0CON1, 1
    movlw 10
    movwf TMR0H, 1	    ;Valor de ref de comp
    ;conf e/s
    movlb 4H
    bcf ANSELF, 0, 1	    ;RF0 digital input
    bsf WPUF, 0, 1	    ;RF0 pullup enabled
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1

inicio:
    movlb 3H
    movf TMR0L, 0, 1
    movlb 4H
    movwf TBLPTRL, 1
    TBLRD*
    movff TABLAT, LATD
    bra inicio
    
    ORG 000200H		    ;datos del decodificador
datos_7s:   DB	3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H     
    
    end yaps






