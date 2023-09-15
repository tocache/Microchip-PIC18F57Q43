    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000700H			    ;dirección de la memoria de programa
		;H   O   L    A
;mensaje:    DB 76H, 3FH, 38H, 77H  
		;P   A   T    O
mensaje:    DB 73H, 77H, 78H, 3FH    		
    
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
    movwf TRISD, 1	;RD6:RD0 como salidas
    movwf ANSELD, 1	;RD6:RD0 como digitales
    movlw 0F0H		;11110000B
    movwf TRISB, 1	;RB3:RB0 como salidas
    movwf ANSELB, 1	;RB3:RB0 como digitales
    clrf LATB, 1	;condicion inicial (los habilitadores de los digitos del display en cero)
    
inicio:
    clrf TBLPTRU, 1
    movlw 07H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;El puntero de tabla esta apuntando a 700H de la mem prog.
    TBLRD*+		;lectura del puntero de tabla y post incremento
    movff TABLAT, LATD	;mueve el contenido de TABLAT hacia LATD
    bsf LATB, 0, 1
    call nopes
    bcf LATB, 0, 1
    TBLRD*+		;lectura del puntero de tabla y post incremento
    movff TABLAT, LATD	;mueve el contenido de TABLAT hacia LATD
    bsf LATB, 1, 1
    call nopes
    bcf LATB, 1, 1
    TBLRD*+		;lectura del puntero de tabla y post incremento
    movff TABLAT, LATD	;mueve el contenido de TABLAT hacia LATD
    bsf LATB, 2, 1
    call nopes
    bcf LATB, 2, 1
    TBLRD*+		;lectura del puntero de tabla y post incremento
    movff TABLAT, LATD	;mueve el contenido de TABLAT hacia LATD
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
    end upcino





