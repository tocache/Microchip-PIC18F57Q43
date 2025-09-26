    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT twisters, class=CODE, reloc=2, abs
twisters:
    ORG 000000H
    bra configuro
    
    ORG 000130H
msj_espaciosx4:	DB 00H, 00H, 00H, 00H    
msj_Peru:	DB 73H, 7BH, 50H, 1CH
msj_espacio:	DB 00H
msj_upcino:	DB 1CH, 73H, 7BH, 58H, 10H, 54H, 5CH    
msj_espaciosx3:	DB 00H, 00H, 00H
	
    ORG 000200H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
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
    ;direccion de apunbte del TBLPTR
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    ;condiciones iniciales
    clrf LATB, 1
    clrf LATD, 1
    movlb 5H
    movlw 34H
    movwf 501H, 1
    movlb 4H
    
inicio:
    call botones
    call multiplexacion
    bra inicio

botones:
    movlb 4H
    btfsc PORTF, 0, 1
    bra alRF1
    movlb 5H
    movlw 3FH
    cpfseq 501H, 1
    bra no_lim1
    movlw 30H
    movwf 501H, 1
    bra sgte1
no_lim1:
    incf 501H, 1, 1
sgte1:
    movlb 4H
    btfss PORTF, 0, 1
    bra sgte1
    return
alRF1:
    btfsc PORTF, 1, 1
    return
    movlb 5H
    movlw 30H
    cpfseq 501H, 1
    bra no_lim2
    movlw 3FH
    movwf 501H, 1
    bra sgte2
no_lim2:
    decf 501H, 1, 1
sgte2:
    movlb 4H    
    btfss PORTF, 1, 1
    bra sgte2
    return
    
multiplexacion:
    movlb 5H
    movf 501H, 0, 1
    movlb 4H
    movwf TBLPTRL, 1	    ;TBLPTR apuntando a 134H
    TBLRD*+		    ;accion de lectura al TBLPTR y post incremento
    movff TABLAT, LATD	    ;nueve contenido de lo leido a RD
    bsf LATB, 0, 1	    ;enciendo primer digito
    call delaycito
    bcf LATB, 0, 1	    ;apago el primer digito
    TBLRD*+		    ;accion de lectura al TBLPTR y post incremento
    movff TABLAT, LATD	    ;nueve contenido de lo leido a RD
    bsf LATB, 1, 1	    ;enciendo segundo digito
    call delaycito
    bcf LATB, 1, 1	    ;apago el segundo digito
    TBLRD*+		    ;accion de lectura al TBLPTR y post incremento
    movff TABLAT, LATD	    ;nueve contenido de lo leido a RD
    bsf LATB, 2, 1	    ;enciendo tercer digito
    call delaycito
    bcf LATB, 2, 1	    ;apago el tercer digito
    TBLRD*		    ;accion de lectura al TBLPTR
    movff TABLAT, LATD	    ;nueve contenido de lo leido a RD
    bsf LATB, 3, 1	    ;enciendo cuarto digito
    call delaycito
    bcf LATB, 3, 1	    ;apago el cuarto digito
    return
    
delaycito:
    movlb 5H
    movlw 20
    movwf 500H, 1
    nop
    decfsz 500H, 1, 1
    bra $-4
    movlb 4H
    return
    
    end twisters

