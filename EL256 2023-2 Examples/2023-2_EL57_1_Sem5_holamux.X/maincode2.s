    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000700H
mensaje:    DB	76H, 3FH, 38H, 77H    
    
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
    clrf LATB, 1	;Condicion inicial: habilitadores todos en cero
inicio:
    clrf TBLPTRU, 1
    movlw 07H
    movwf TBLPTRH,1
    clrf TBLPTRL, 1	;TBLPTR esta apuntando a la direccion 700H de mem prog
    TBLRD*+		;Lee el contenido de TBLPTR (700H) y luego lo incrementa
    movff TABLAT, LATD	;Mueve el contenido de TABLAT hacia LATD
    bsf LATB, 0, 1	;habilito digito 0
    call nopes
    bcf LATB, 0, 1	;deshabilitdo digito 0
    TBLRD*+		;Lee el contenido de TBLPTR (701H) y luego lo incrementa
    movff TABLAT, LATD	;Mueve el contenido de TABLAT hacia LATD
    bsf LATB, 1, 1	;habilito digito 1
    call nopes
    bcf LATB, 1, 1	;deshabilito digito 1
    TBLRD*+		;Lee el contenido de TBLPTR (702H) y luego lo incrementa
    movff TABLAT, LATD	;Mueve el contenido de TABLAT hacia LATD
    bsf LATB, 2, 1	;habilito digito 2
    call nopes
    bcf LATB, 2, 1	;deshabilitdo digito 2
    TBLRD*+		;Lee el contenido de TBLPTR (703H) y luego lo incrementa
    movff TABLAT, LATD	;Mueve el contenido de TABLAT hacia LATD
    bsf LATB, 3, 1	;habilito digito 3
    call nopes
    bcf LATB, 3, 1	;deshabilito digito 3
    bra inicio
    
nopes:
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
    end upcino



