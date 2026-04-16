;Este es un comentario
    ;Modelo de CPU
    PROCESSOR 18F57Q43
    ;llamado a la cabecera
    #include "cabecera.inc"
    
    ;declaracion del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;vector de RESET
    bra configuro   ;salto a label configuro
    
    ORG 000100H	    ;zona de programa de usuario
configuro:    
    ;conf del modulo de oscilador
    movlb 0H	    ;voy al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;FRQ = 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;conf de las E/S
    movlb 4H		;voy al Bank4
    bsf TRISC, 0, 1	;RC0 como entrada
    bcf ANSELC, 0, 1	;RC0 como digital
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital
    
inicio:
    btfsc PORTC, 0, 1	;pregunto si RC0 es cero
    bra es_falso	;rpta falso, salta a label es_falso
    btfsc PORTE, 0, 1	;rpta verdad, pregunto si RE0 es cero
    bra es_falso	;rpta falso, salta a label es_falso
    bsf LATF, 0, 1	;rpta verdad, RF0=1 o prendo el LED
    bra inicio		;salta a label inicio
es_falso:
    bcf LATF, 0, 1	;RF0=0 o apagado el LED
    bra inicio		;salto a label inicio

    end upcino