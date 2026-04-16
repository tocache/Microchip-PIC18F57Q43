;Este es un comentario
    ;Seleccion del CPU
    PROCESSOR 18F57Q43
    ;Llamado a la cabecera
    #include "cabecera.inc"
    
    ;Creacion del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;vector de RESET
    bra configuro   ;salto a label configuro
    
    ORG 000100H	    ;zona de programa de usuario
configuro:
    ;conf el modulo de oscilador
    movlb 0H	    ;me voy al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC corriendo a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;conf de las E/S
    movlb 4H		;me voy al Bank4
    bsf TRISD, 0, 1	;RD0 como entrada
    bsf TRISD, 1, 1	;RD1 como entrada
    bcf ANSELD, 0, 1	;RD0 como digital
    bcf ANSELD, 1, 1	;RD1 cmo digital
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital
    
inicio:
    btfsc PORTD, 0, 1	;Pregunto si RD0 es cero
    bra es_falso	;rpta falso, salto a label es_falso
    btfsc PORTD, 1, 1	;rpta verdad, pregunto si RD1 es cero
    bra es_falso	;rpta falso, salto a label es_falso
    bsf LATF, 0, 1	;rpta verdad, RF0=1
    bra inicio		;salto a label inicio
es_falso:
    bcf LATF, 0, 1	;RF0=0
    bra inicio		;salto a label inicio
    
    end upcino
    
    


