;Este es el primer comentario
;Este primer ejemplo es la implementación
;de una compuerta NOT de un bit
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;vector de RESET
    bra configuro   ;salto a label configuro
    
    ORG 000100H
configuro:    
    movlb 0H		;me voy al Bank0
    movlw 60H
    movwf OSCCON1, 1	;selecciono HFINTOSC y div a 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC trabaja a 4MHz
    movlb 4H		;me voy al Bank4
    bsf TRISF, 0, 1	;RF0 es entrada
    bcf ANSELF, 0, 1	;RF0 es digital
    bcf TRISB, 0, 1	;RB0 es salida
    bcf ANSELB, 0, 1	;RB0 es digital
inicio_not:
    btfss PORTF, 0, 1	;Pregunto si RF0 es uno
    bra falsazo		;Falso, salta a etiqueta falsazo
    bcf LATB, 0, 1	;Verdad, RB0 a cero lógico
    bra inicio_not	;Salta a label inicio_not
falsazo:
    bsf LATB, 0, 1	;RB0 a uno lógico
    bra inicio_not	;Salta a label inicio_not
    
    end upcino
    


