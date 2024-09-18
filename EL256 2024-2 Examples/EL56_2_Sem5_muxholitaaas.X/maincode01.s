    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 003000H
p_hola: DB 76H, 3FH, 38H, 77H
 
    ORG 000100H
configuro:
    ;configuro la fuente de reloj
    movlb 0H
    movlw 56H
    movwf OSCCON1, 1	    ;NOSC=LFINTOSC, NDIV=1:64
    movlw 10H
    movwf OSCEN, 1	    ;LFINTOSC enabled
    ;configuro E/S
    movlb 4H
    movlw 0F0H		    ;11110000
    movwf TRISB, 1	    ;RB[3:0] como salidas
    movwf ANSELB, 1	    ;RB[3:0] como digitales
    movlw 80H
    movwf TRISD, 1	    ;RD[6:0] como salidas
    movwf ANSELD, 1	    ;RD[6:0] como digitales}
    ;configuraciones iniciales adicionales
    clrf LATB, 1	    ;RB[3:0] en cero (digitos disabled)
    clrf TBLPTRU, 1
    movlw 30H
    movwf TBLPTRH, 1

inicio_muxi:
    movlw LOW p_hola
    movwf TBLPTRL, 1	    ;TBLPTR apuntando a direccion 003000H
    TBLRD*+		    ;leo lo apuntado con posterior incremento de TBLPTR
    movff TABLAT, LATD	    ;muevo contenido leido a RD
    bsf LATB, 0, 1	    ;habilitamos primer digito
    call nopes		    ;unos cuantos nops
    bcf LATB, 0, 1	    ;deshabilitamos primer digito
    TBLRD*+		    ;leo lo apuntado con posterior incremento de TBLPTR
    movff TABLAT, LATD	    ;muevo contenido leido a RD
    bsf LATB, 1, 1	    ;habilitamos segundo digito
    call nopes		    ;unos cuantos nops
    bcf LATB, 1, 1	    ;deshabilitamos segundo digito
    TBLRD*+		    ;leo lo apuntado con posterior incremento de TBLPTR
    movff TABLAT, LATD	    ;muevo contenido leido a RD
    bsf LATB, 2, 1	    ;habilitamos tercer digito
    call nopes		    ;unos cuantos nops
    bcf LATB, 2, 1	    ;deshabilitamos tercer digito
    TBLRD*+		    ;leo lo apuntado con posterior incremento de TBLPTR
    movff TABLAT, LATD	    ;muevo contenido leido a RD
    bsf LATB, 3, 1	    ;habilitamos cuarto digito
    call nopes		    ;unos cuantos nops
    bcf LATB, 3, 1	    ;deshabilitamos cuarto digito
    bra inicio_muxi
    
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
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
    end upcino