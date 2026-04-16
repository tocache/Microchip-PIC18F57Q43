;Este es un comentario
    ;Modelo de CPU
    PROCESSOR 18F57Q43
    ;Llamado a la cabecera
    #include "cabecera.inc"
    
    ;declaracion del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de RESET
    bra configuro	;salto a label configuro
    
    ORG 000100H		;zona de programa de usuario
configuro:
    ;configuraciones de modulos perifericos
    ;conf el modulo de oscilador
    movlb 0H		;al bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;conf las E/S
    movlb 4H		;al Bank4
    bsf TRISD, 0, 1	;RD0 como entrada
    bcf ANSELD, 0, 1	;RD0 como digital
    bsf TRISD, 1, 1	;RD1 como entrada
    bcf ANSELD, 1, 1	;RD1 como digital
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital
    
inicio:			;inicio de tu algoritmo
    btfss PORTD, 0, 1	;pregunto si RD0=1
    bra es_falso	;rpta falso, salto a label es_falso
    btfss PORTD, 1, 1	;rpta verdad, pregunta si RD1=1
    bra es_falso	;rpta falso, salto a label es_falso
    bsf LATF, 0, 1	;rpta verdad, RF0=1
    bra inicio		;salto a label inicio
es_falso:
    bcf LATF, 0, 1	;RF0=0
    bra inicio		;salto a label inicio
    end upcino
    


