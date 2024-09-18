    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 005000H
p_hola: DB 76H, 3FH, 38H, 77H
p_chau: DB 39H, 76H, 77H, 3EH
    
    ORG 000100H
configuro:
    ;fuente de reloj
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC=4MHZ
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;conf de las E/S
    movlb 4H
    movlw 80H		;10000000
    movwf TRISD, 1	;RD[6:0] como salidas
    movwf ANSELD, 1	;RD[6:0] como digitales
    movlw 0F0H		;11110000
    movwf TRISB, 1	;RB[3:0] como salidas
    movwf ANSELB, 1	;RB[3:0] como digitales
    bsf TRISB, 4, 1	;RB4 es una entrada
    bcf ANSELB, 4, 1	;RB4 como digital
    bsf WPUB, 4, 1	;RB4 con pullup activada
    ;configuraciones iniciales adicionales
    clrf LATB, 1	;habilitadores de los digitos en cero
    clrf TBLPTRU, 1
    movlw 50H
    movwf TBLPTRH, 1
    
inicio_mux:
    btfsc PORTB, 4, 1	;pregunto si boton presionado
    bra no_presione
    bra si_presione

no_presione:
    movlw LOW p_hola    
    bra siguiente
si_presione:    
    movlw LOW p_chau    

siguiente:    
    movwf TBLPTRL, 1	;TBLPTR apuntando a 005000H o 5004H
    TBLRD*+		;leo lo apuntado por TBLPTR post incremento
    movff TABLAT, LATD	;mando a RD lo leido
    bsf LATB, 0, 1	;habilito primer digito
    call nopsx32
    bcf LATB, 0, 1	;deshabilitamos el primer digito
    TBLRD*+		;leo lo apuntado por TBLPTR post incremento
    movff TABLAT, LATD	;mando a RD lo leido
    bsf LATB, 1, 1	;habilito segundo digito
    call nopsx32
    bcf LATB, 1, 1	;deshabilitamos el segundo digito
    TBLRD*+		;leo lo apuntado por TBLPTR post incremento
    movff TABLAT, LATD	;mando a RD lo leido
    bsf LATB, 2, 1	;habilito tercer digito
    call nopsx32
    bcf LATB, 2, 1	;deshabilitamos el tercer digito
    TBLRD*+		;leo lo apuntado por TBLPTR post incremento
    movff TABLAT, LATD	;mando a RD lo leido
    bsf LATB, 3, 1	;habilito cuarto digito
    call nopsx32
    bcf LATB, 3, 1	;deshabilitamos el cuarto digito
    bra inicio_mux
    
nopsx32:
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


