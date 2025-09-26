    PROCESSOR 18F57Q43
    #include "cabecera.inc"

X_VAR	EQU 500H
POSICION EQU 501H    
    
    PSECT toasted, class=CODE, reloc=2, abs
toasted:
    ORG 000000H
    bra configuro
    
    ORG 000123H
espaciox4:  DB	00H, 00H, 00H, 00H    
doctor:	    DB	5EH, 5CH, 58H, 78H, 5CH, 50H
espaciox1:  DB	00H	    
ucchelly:   DB	3EH, 58H, 58H, 74H, 7BH, 30H, 30H, 6EH
espaciox3:  DB	00H, 00H, 00H
    
    ORG 000200H
configuro:
    ;conf mod osc a 4MHz
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
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
    ;conf TBLPTRL
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    movlw 23H
    movwf TBLPTRL, 1
    ;cond iniciales
    clrf LATB, 1
    clrf LATD, 1
    movlb 5H
    movlw 23H
    movwf 501H, 1
    movlb 4H
    
inicio:
    call botones
    call multiplexacion
    bra inicio
    
botones:
    btfsc PORTF, 0, 1
    bra sgte_btn
    movlb 5H
    movlw 35H
    cpfseq POSICION, 1
    bra incremento
    movlw 23H
    movwf POSICION, 1
    bra sueltoRF0
incremento:
    incf POSICION, 1, 1
sueltoRF0:
    movlb 4H
    btfss PORTF, 0, 1
    bra sueltoRF0
    return
sgte_btn:
    btfsc PORTF, 1, 1
    return
    movlb 5H
    movlw 23H
    cpfseq POSICION, 1
    bra decremento
    movlw 35H
    movwf POSICION, 1
    bra sueltoRF1
decremento:
    decf POSICION, 1, 1
sueltoRF1:
    movlb 4H
    btfss PORTF, 1, 1
    bra sueltoRF1
    return
    
multiplexacion:
    movlb 5H
    movf POSICION, 0, 1
    movlb 4H
    movwf TBLPTRL, 1
    TBLRD*+
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 0, 1
    call miniretardo
    bcf LATB, 0, 1
    TBLRD*+
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 1, 1
    call miniretardo
    bcf LATB, 1, 1
    TBLRD*+
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 2, 1
    call miniretardo
    bcf LATB, 2, 1
    TBLRD*
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 3, 1
    call miniretardo
    bcf LATB, 3, 1
    return
   
miniretardo:
    movlb 5H
    movlw 20
    movwf X_VAR, 1
    nop
    decfsz X_VAR, 1, 1
    bra $-4
    movlb 4H
    return
    
    end toasted



