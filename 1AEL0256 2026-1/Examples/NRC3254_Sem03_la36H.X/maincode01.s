    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de RESET
    bra configuro
    
    ORG 000100H		;zona de programa de usuario
configuro:
    ;conf el modulo de oscilador
    movlb 0H		;Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf las E/S
    movlb 4H		    ;Bank4
    clrf TRISD, 1	    ;RD como salidas
    clrf ANSELD, 1	    ;RD como digitales
    bsf TRISC, 5, 1	    ;RC5 como entrada
    bcf ANSELC, 5, 1	    ;RC5 como digital
    bsf WPUC, 5, 1	    ;RC5 con pullup activado
    
inicio:
    btfsc PORTC, 5, 1	    ;pregunto si RC5 es cero
    bra es_falso	    ;rpta falso, salto a label es_falso
    movlw 0AAH		    ;rpta verdad, muevo 69H a Wreg
    movwf LATD, 1	    ;muevo Wreg a RD
    bra inicio		    ;salto a label inicio
es_falso:
    movlw 55H		    ;muevo 36H a Wreg
    movwf LATD, 1	    ;muevo Wreg hacia RD
    bra inicio		    ;salto a label inicio

    
    end upcino





