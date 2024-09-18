    PROCESSOR 18F57Q43
    #include "cabecera.inc"

estado_msg EQU	500H	    ;etiqueta a GPR 500H    
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000600H
pal_hola:   DB 76H, 3FH, 38H, 77H    
pal_papa:   DB 73H, 77H, 73H, 77H 
pal_bica:   DB 7CH, 10H, 58H, 5FH   
    
    ORG 000100H
configuro:
    ;configuro la fuente de reloj
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV=1:1
    movlw 04H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz 
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configuro las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD[6:0] como salidas
    movwf ANSELD, 1	;RD[6:0] como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB[3:0] como salidas
    movwf ANSELB, 1	;RB[3:0] como digitales
    bsf TRISB, 4, 1	;RB4 como entrada
    bcf ANSELB, 4, 1	;RB4 como digital
    bsf WPUB, 4, 1	;RB4 con pullup activada
    ;condiciones iniciales
    clrf LATB, 1	;RB[3:0] a cero, digitos deshabilitados
    clrf TBLPTRU, 1	;TBLPTRU = 00H
    movlw 06H
    movwf TBLPTRH, 1	;TBLPTRH = 06H
    ;clrf TBLPTRL, 1	;TBLPTRL = 00H
    movlb 5H
    clrf estado_msg, 1	;estado_msg = 0
    movlb 4H
    
inicio_mux:
    btfsc PORTB, 4, 1	;Preguntar si presione el RB4
    bra no_presione	;Falso
    bra si_presione	;Verdad
no_presione:
    movlb 5H
    movlw 0
    cpfseq estado_msg, 1   ;pregunto si estado_msg = 0
    bra sigo1
    movlb 4H
    movlw LOW pal_hola
    bra siguiente
sigo1:
    movlw 1
    cpfseq estado_msg, 1   ;pregunto si estado_msg = 1
    bra sigo2
    movlb 4H
    movlw LOW pal_papa
    bra siguiente
sigo2:
    movlw 2
    cpfseq estado_msg, 1   ;pregunto si estado_msg = 1
    bra inicio_mux
    movlb 4H
    movlw LOW pal_bica
    bra siguiente
    
si_presione:
    ;yo quiero que salga la palabra PAPA
    movlb 5H
    movlw 02H
    cpfseq estado_msg, 1	;pregunto su estado_msg = 2
    bra no_es_dos
    bra si_es_dos
no_es_dos:
    incf estado_msg, 1, 1	;incremento estado_msg
    bra siguiente2
si_es_dos:
    clrf estado_msg, 1	;pongo a cero estado_msg
siguiente2:
    movlb 4H
    btfss PORTB, 4, 1	;pregunto si solte el boton RB4
    bra $-2		;aun mantengo pulsado RB4
    bra inicio_mux

siguiente:    
    movwf TBLPTRL, 1	;TBLPTRL = pal_hola
    TBLRD*+		;lectura del TLBPTR con post incremento (600H)
    movff TABLAT, LATD	;muevo contenido de TABLAT a RD
    bsf LATB, 0, 1	;habilitamos primer digito
    call nopesx32
    bcf LATB, 0, 1	;deshabilitamos primer digito
    TBLRD*+		;lectura del TLBPTR con post incremento (601H)
    movff TABLAT, LATD	;muevo contenido de TABLAT a RD
    bsf LATB, 1, 1	;habilitamos segundo digito
    call nopesx32
    bcf LATB, 1, 1	;deshabilitamos segundo digito
    TBLRD*+		;lectura del TLBPTR con post incremento (602H)
    movff TABLAT, LATD	;muevo contenido de TABLAT a RD
    bsf LATB, 2, 1	;habilitamos tercer digito
    call nopesx32
    bcf LATB, 2, 1	;deshabilitamos tercer digito
    TBLRD*+		;lectura del TLBPTR con post incremento (603H)
    movff TABLAT, LATD	;muevo contenido de TABLAT a RD
    bsf LATB, 3, 1	;habilitamos cuarto digito
    call nopesx32
    bcf LATB, 3, 1	;deshabilitamos cuarto digito
    bra inicio_mux
    
nopesx32:
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







