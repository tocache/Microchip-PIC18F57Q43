;Programa para visualizar HOLA en el disp mux 4 dig 7 segm CC
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
POSICION EQU 500H	;colocando label a 500H de mem datos (GPR)    
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H
    bra configuro
    
    ORG 000100H
texto_7s:   DB 00H, 00H, 00H, 00H, 39H, 1CH, 50H, 10H, 5CH, 6DH, 10H, 78H, 6EH, 00H, 54H, 5FH, 54H, 5CH, 00H, 00H, 00H
    
    ORG 000200H
configuro:
    ;conf modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	;HFINTOSC 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 50H
    movwf OSCEN, 1	;HFINTOSC enabled y LFINTOSC enabled
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 son salidas
    movwf ANSELD, 1	;RD6 al RD0 son digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3 al RB0 son salidas
    movwf ANSELB, 1	;RB3 al RB0 son digitales
    movlw 0FCH		;RF1 y RF0 por defecto son entradas
    movwf ANSELF, 1	;RF1 y RF0 son digitales
    movlw 03H
    movwf WPUF, 1	;RF1 y RF0 con pullup activadas
    ;direccion de apunte del TBLPTR
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    movlw 04H
    movwf TBLPTRL, 1	;TBLPTR apuntando a 104H de la mem prog
    ;condiciones iniciales de operacion
    clrf LATD, 1	;todo el puerto RD en cero
    clrf LATB, 1	;todo el puerto RB en cero
    movlb 5H
    clrf POSICION, 1	;GPR POSICION a cero
    movlb 4H
    
inicio:
    btfsc PORTF, 0, 1	;pregunto si RF0=0 (presione btn)
    bra sgte_btn	;falso, salta a label sgte_btn
    movlb 5H
    movlw 17
    cpfseq POSICION, 1	;pregunto si POSICION=7
    bra incremento	;falso, salta a label incrementa
    clrf POSICION, 1	;verdad, GPR POSICION=0
    bra union1
incremento:
    incf POSICION, 1, 1	;incremento de GPR POSICION
union1:
    movlb 4H
    btfss PORTF, 0, 1	;pregunto si RF0=1 (solte btn)
    bra union1
    bra union3
sgte_btn:
    btfsc PORTF, 1, 1	;pregunto si RF1=0 (si presione btn)
    bra union3
    movlb 5H
    movlw 0
    cpfseq POSICION, 1	;pregunto si GPR POSICION=0
    bra decremento	;falso salta a label decremento
    movlw 17
    movwf POSICION, 1	;verdad, GPR POSICION=7
    bra union2
decremento:
    decf POSICION, 1, 1	;decremento GPR POSICION
union2:
    movlb 4H
    btfss PORTF, 1, 1	;pregunta si RF1=1 (si soltaste btn)
    bra union2
union3:    
    call multiplex
    bra inicio

multiplex:
    movlb 5H
    movf POSICION, 0, 1	;obtengo el valor de GPR POSICION
    movlb 4H
    movwf TBLPTRL, 1	;TBLPTR apuntando a 100H de la mem prog
    TBLRD*+		;accion de lectura y posterior incremento de TBLPTR
    movff TABLAT, LATD	;mover contenido de TABLAT hacia RD
    bsf LATB, 0, 1	;RB0=1, habilito primer digito del display
    call nopes
    bcf LATB, 0, 1	;RB0=0, deshabilitado el primer digito del display
    TBLRD*+		;accion de lectura y posterior incremento de TBLPTR
    movff TABLAT, LATD	;mover contenido de TABLAT hacia RD
    bsf LATB, 1, 1	;RB0=1, habilito segundo digito del display
    call nopes
    bcf LATB, 1, 1	;RB0=0, deshabilitado el segundo digito del display
    TBLRD*+		;accion de lectura y posterior incremento de TBLPTR
    movff TABLAT, LATD	;mover contenido de TABLAT hacia RD
    bsf LATB, 2, 1	;RB0=1, habilito primer digito del display
    call nopes
    bcf LATB, 2, 1	;RB0=0, deshabilitado el primer digito del display
    TBLRD*		;accion de lectura
    movff TABLAT, LATD	;mover contenido de TABLAT hacia RD
    bsf LATB, 3, 1	;RB0=1, habilito primer digito del display
    call nopes
    bcf LATB, 3, 1	;RB0=0, deshabilitado el primer digito del display
    return
    
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
    
    end upcinos
    





