;Programa para visualizar HOLA en el disp mux 4 dig 7 segm CC
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H
    bra configuro
    
    ORG 000100H
texto_7s:   DB 00H, 00H, 00H, 00H, 39H, 5CH, 38H, 5FH, 00H, 00H, 00H
    
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
    ;direccion de apunte del TBLPTR
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    movlw 04H
    movwf TBLPTRL, 1	;TBLPTR apuntando a 104H de la mem prog
    ;condiciones iniciales de operacion
    clrf LATD, 1	;todo el puerto RD en cero
    clrf LATB, 1	;todo el puerto RB en cero
    
inicio:
    movlw 04H
    movwf TBLPTRL, 1	;TBLPTR apuntando a 104H de la mem prog
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
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
    end upcinos
    