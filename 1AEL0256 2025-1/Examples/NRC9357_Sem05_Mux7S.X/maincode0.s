;Programa para visualizar la palabra dato en el display multiplexado
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 007000H
    ;		 d    a    t    o
msg_dato: DB	5EH, 5FH, 78H, 5CH    
 
    ORG 000100H
configuro:
    ;configurar la fuente de reloj o modulo de oscilador
    movlb 0H	    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
;    movlw 55H
;    movwf OSCCON1, 1	;NOSC=LFINTOSC, NDIV=1:32
;    movlw 10H
;    movwf OSCEN, 1	;LFINTOSC enabled, LFINTOSC a 1KHz aprox
    ;configuracion de las E/S
    movlb 4H		;al Bank4
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 como salidas
    movwf ANSELD, 1	;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3 al RB0 como salidas
    movwf ANSELB, 1	;RB3 al RB0 como digitales
    ;establecer direccion de apunto del TBLPTR
    clrf TBLPTRU, 1
    movlw 70H
    movwf TBLPTRH, 1
    ;condicion inicial de habilitadores en cero
    clrf LATB, 1
    
inicio:
    clrf TBLPTRL, 1	;TBLPTR apuntando a la direccion 7000H
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0, 1
    call nopis
    bcf LATB, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1, 1
    call nopis
    bcf LATB, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2, 1
    call nopis
    bcf LATB, 2, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 3, 1
    call nopis
    bcf LATB, 3, 1
    TBLRD*
    movff TABLAT, LATD
    bra inicio
    
nopis:
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


