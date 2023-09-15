    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE,reloc=2, abs
upcino:
    ORG 000000H		;Vector de RESET
    bra configuro
    
    ORG 000200H		;Direccion de memoria de programa
		;H    O    L    A
;mensaje:    DB	76H, 3FH, 38H, 77H    
		;C    E    R    O
mensaje:    DB	39H, 79H, 50H, 3FH    
		
    ORG 000100H
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
    movwf TRISD, 1	;RD6-RD0 como salidas
    movwf ANSELD, 1	;RD6-RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3-RB0 como salidas
    movwf ANSELB, 1	;RB3-RB0 como digitales
    clrf LATB, 1	;Habilitadores en cero (cond inicial)
    
inicio:
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL,1	;El TBLPTR esta mirando a dirección 200H de mem prog.
    TBLRD*+		;Lectura del contenido apuntado por TBLPTR y post incremento
    movff TABLAT, LATD
    bsf LATB, 0, 1
    call nopes
    bcf LATB, 0, 1
    TBLRD*+		;Lectura del contenido apuntado por TBLPTR y post incremento
    movff TABLAT, LATD
    bsf LATB, 1, 1
    call nopes
    bcf LATB, 1, 1
    TBLRD*+		;Lectura del contenido apuntado por TBLPTR y post incremento
    movff TABLAT, LATD
    bsf LATB, 2, 1
    call nopes
    bcf LATB, 2, 1
    TBLRD*+		;Lectura del contenido apuntado por TBLPTR y post incremento
    movff TABLAT, LATD
    bsf LATB, 3, 1
    call nopes
    bcf LATB, 3, 1
    bra inicio
    
nopes:
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





