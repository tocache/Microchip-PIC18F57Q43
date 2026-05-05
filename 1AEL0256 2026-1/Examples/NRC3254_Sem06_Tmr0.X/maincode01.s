    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
N_PALABRA EQU 501H	;GPR 501H
    
    PSECT chesss, class=CODE, reloc=2, abs
chesss:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf mod osc
    movlb 0H
    movlw 50H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1
    ;conf Timer0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1
    movlw 0AAH
    movwf T0CON1, 1    
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    movlw 0FCH
    movwf ANSELF, 1
    movlw 03H
    movwf WPUF, 1
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 08H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    ;cond iniciales
    clrf LATB, 1	    ;habilitadores G1, G2, G3, G4 apagados
    movlb 5H
    movlw 1
    movwf N_PALABRA, 1	    ;N_PALABRA=1
    movlb 4H
    
inicio:
    movlb 4H
    btfss PIR3, 7, 1	    ;pregunto si TMR0IF=1
    bra finalaso
    bcf PIR3, 7, 1	    ;bajamos bandera TMR0IF
    movlb 5H
    movlw 4
    cpfseq N_PALABRA, 1
    bra incremento
    movlw 1
    movwf N_PALABRA, 1
    bra finalaso
incremento:
    incf N_PALABRA, 1, 1
finalaso:    
    call multiplexacion
    bra inicio

multiplexacion:
    movlb 5H
    movlw 1
    cpfseq N_PALABRA, 1
    bra noesuno
    movlb 4H
    movlw 00H
    bra final
noesuno:
    movlw 2
    cpfseq N_PALABRA, 1
    bra noesdos
    movlb 4H
    movlw 04H
    bra final
noesdos:
    movlw 3
    cpfseq N_PALABRA, 1
    bra noestres
    movlb 4H
    movlw 08H
    bra final
noestres:
    movlb 4H
    movlw 0CH
    bra final
    
final:    
    
    movwf TBLPTRL, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0, 1
    call micro_delay
    bcf LATB, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1, 1
    call micro_delay
    bcf LATB, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2, 1
    call micro_delay
    bcf LATB, 2, 1
    TBLRD*
    movff TABLAT, LATD
    bsf LATB, 3, 1
    call micro_delay
    bcf LATB, 3, 1
    return
    
micro_delay:
    movlb 5H
    movlw 5
    movwf 500H, 1
    nop
    decfsz 500H, 1, 1
    bra $-4
    movlb 4H
    return

    ORG 000800H
str_chau: DB 58H, 74H, 5FH, 1CH
str_pera: DB 73H, 7BH, 50H, 5FH
str_foca: DB 71H, 5CH, 58H, 5FH
str_luna: DB 38H, 1CH, 54H, 5FH
    
    end chesss


