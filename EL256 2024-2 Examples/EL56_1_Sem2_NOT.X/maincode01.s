;Hola mundo, este es un comentario
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    ;Creacion del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro	;salto a label configuro
    
    ORG 000100H		;zona de usuario libre
configuro:    
    ;configuracion de fuente de reloj
    movlb 0H		;nos vamos al Bank0
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 60H
    movwf OSCCON1, 1	;NOSC a HFINTOSC, NDIV a 1:1
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC habilitado
    ;configuracion de las E/S
    movlb 4H		;nos vamos al Bank4
    bsf TRISD, 0, 1	;RD0 como entrada
    bcf ANSELD, 0, 1	;RD0 como digital
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital

inicio_NOT:
    btfss PORTD, 0, 1	;Pregunto si RD0 es uno
    bra falsazo		;Falso, salto a label falsazo
    bcf LATF, 0, 1	;Verdad, RF0 a cero
    bra inicio_NOT	;Salto a inicio_NOT
falsazo:
    bsf LATF, 0, 1	;RF0 a uno
    bra inicio_NOT	;Salto a inicio_NOT
    
    end upcino

