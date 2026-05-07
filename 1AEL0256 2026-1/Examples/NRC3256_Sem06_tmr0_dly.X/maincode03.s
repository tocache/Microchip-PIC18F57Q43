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
    ;conf TMR0
    movlb 3H
    movlw 90H
    movwf T0CON0, 1
    movlw 0A1H
    movwf T0CON1, 1
    ;conf E/S
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    clrf TRISF, 1
    clrf ANSELF, 1
    ;TBLPTR
    clrf TBLPTRU, 1
    movlw 09H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    ;cond inicial
    movlb 5H
    clrf 501H, 1
    
inicio:
    movlb 3H
    movlw 3CH
    movwf TMR0H, 1
    movlw 0B0H
    movwf TMR0L, 1	;cta inicial 15536 en TMR0
    movlb 4H
otro:    
    btfss PIR3, 7, 1	;preg si TMR0 se desbordo
    bra multiplex
    bcf PIR3, 7, 1
    btg LATC, 0, 1
    movlb 5H
    movlw 38
    cpfseq 501H, 1
    bra incrementa
    clrf 501H, 1
    bra inicio
incrementa:
    incf 501H, 1, 1
    bra inicio
    
multiplex:
    movlb 5H
    movf 501H, 0, 1
    movlb 4H
    movwf TBLPTRL, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 0, 1
    call micro_delay
    bcf LATF, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 1, 1
    call micro_delay
    bcf LATF, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 2, 1
    call micro_delay
    bcf LATF, 2, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 3, 1
    call micro_delay
    bcf LATF, 3, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 4, 1
    call micro_delay
    bcf LATF, 4, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 5, 1
    call micro_delay
    bcf LATF, 5, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATF, 6, 1
    call micro_delay
    bcf LATF, 6, 1
    TBLRD*
    movff TABLAT, LATD
    bsf LATF, 7, 1
    call micro_delay
    bcf LATF, 7, 1
    bra otro
    
micro_delay:
    movlb 5H
    movlw 5
    movwf 500H, 1
    nop
    decfsz 500H, 1, 1
    bra $-4
    movlb 4H
    return    

    ORG 000900H
msg_1:	DB	00H, 00H, 00H, 00H, 00H, 00H, 00H, 00H
msg_2:	DB	1CH, 5CH, 6EH, 00H, 5FH, 00H, 5FH, 73H
msg_3:	DB	50H, 5CH, 7CH, 5FH, 50H, 00H, 38H, 5FH
msg_4:	DB	00H, 73H, 58H, 06H, 00H, 5EH, 7BH, 00H	
msg_5:	DB	15H, 06H, 58H, 50H, 5CH, 00H, 00H, 00H
msg_6:	DB	00H, 00H, 00H, 00H, 00H, 00H, 00H
    
    end yaps


