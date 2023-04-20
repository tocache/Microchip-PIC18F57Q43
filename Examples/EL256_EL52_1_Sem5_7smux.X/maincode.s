    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000800H
	    ;C   O   S   A
mensaje: DB 39H,3FH,6DH,77H    
    
    ORG 000020H
configuro:
    movlb 0H
    movlw 69H		    ;NDIV en 1:128
    movwf OSCCON1
    movlw 00H		
    movwf OSCFRQ	    ;HFINTOSC a 1MHz
    movlw 40H
    movwf OSCEN
    movlb 4H
    movlw 80H
    movwf TRISB
    movwf ANSELB
    movlw 0F0H
    movwf TRISA
    movwf ANSELA
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL

inicio:    
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 0
    call nops
    bcf LATA, 0
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 1
    call nops
    bcf LATA, 1
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 2
    call nops
    bcf LATA, 2
    TBLRD*
    movff TABLAT, LATB
    bsf LATA, 3
    call nops
    bcf LATA, 3
    clrf TBLPTRL
    bra inicio
    
nops:
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
