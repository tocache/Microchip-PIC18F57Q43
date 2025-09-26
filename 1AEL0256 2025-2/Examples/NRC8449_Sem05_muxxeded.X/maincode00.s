    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
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
    ;conf TBLPTRL
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    movlw 27H
    movwf TBLPTRL, 1
    ;cond iniciales
    clrf LATB, 1
    clrf LATD, 1
    
inicio:
    call multiplexacion
    bra inicio
    
multiplexacion:
    movlw 27H
    movwf TBLPTRL, 1
    TBLRD*
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 0, 1
    call miniretardo
    bcf LATB, 0, 1
    incf TBLPTRL, 1, 1
    TBLRD*
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 1, 1
    call miniretardo
    bcf LATB, 1, 1
    incf TBLPTRL, 1, 1
    TBLRD*
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 2, 1
    call miniretardo
    bcf LATB, 2, 1
    incf TBLPTRL, 1, 1
    TBLRD*
    movf TABLAT, 0, 1
    movwf LATD, 1
    bsf LATB, 3, 1
    call miniretardo
    bcf LATB, 3, 1
    return
   
;miniretardo:
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    nop
;    return
    
miniretardo:
    movlb 5H
    movlw 20
    movwf 500H, 1
    nop
    decfsz 500H, 1, 1
    bra $-4
    movlb 4H
    return
    
    end toasted
