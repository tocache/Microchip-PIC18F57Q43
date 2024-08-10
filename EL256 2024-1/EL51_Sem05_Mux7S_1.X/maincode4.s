    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000500H
tabla_mensaje1:	DB 73H, 79H, 50H, 3EH	;PERU
	
    ORG 000600H
tabla_mensaje2:	DB 76H, 3FH, 38H, 77H	;HOLA
        
    ORG 000100H
configuro:    
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 00H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    clrf TRISD, 1
    clrf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movlw 0E0H
    movwf ANSELB, 1
    bsf WPUB, 4, 1
    clrf LATB, 1
    clrf TBLPTRU, 1
    
inicio:
    call pregunta_btn
    clrf TBLPTRL, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0, 1
    call nopx16
    bcf LATB, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1, 1
    call nopx16
    bcf LATB, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2, 1
    call nopx16
    bcf LATB, 2, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 3, 1
    call nopx16
    bcf LATB, 3, 1
    bra inicio
  
pregunta_btn:
    btfsc PORTB, 4, 1
    bra msg_hola
    bra msg_peru
    
msg_hola:
    movlw 06H
    movwf TBLPTRH, 1
    return
    
msg_peru:
    movlw 05H
    movwf TBLPTRH, 1    
    return
    
nopx16:
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
    nop
    nop
    nop
    nop
    nop
    nop
    return

    end upcino








