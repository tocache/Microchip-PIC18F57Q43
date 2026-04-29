    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT ARGH, class=CODE, reloc=2, abs
ARGH:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf modulo oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC, NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
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
    ;conf el TBLPTR
    clrf TBLPTRU, 1
    movlw 03H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;TBLPTR apunta a 000300H
    
inicio:
    movf PORTF, 0, 1
    andlw 03H
    movlb 5H
    movwf 500H, 1
    movlw 00H
    cpfseq 500H, 1
    bra siguiente1
    movlb 4H
    movlw 00H
    call multiplexacion
    bra inicio    
siguiente1:
    movlw 01H
    cpfseq 500H, 1
    bra siguiente2
    movlb 4H
    movlw 04H
    call multiplexacion
    bra inicio
siguiente2:
    movlw 02H
    cpfseq 500H, 1
    bra siguiente3
    movlb 4H
    movlw 08H
    call multiplexacion
    bra inicio    
siguiente3:
    movlb 4H
    movlw 0CH
    call multiplexacion
    bra inicio

multiplexacion:
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
    
    ORG 000300H
str_gato: DB 6FH,5FH,78H,5CH
str_lobo: DB 38H,5CH,7CH,5CH
str_nube: DB 54H,1CH,7CH,7BH
str_cafe: DB 58H,5FH,71H,7BH

    end ARGH





