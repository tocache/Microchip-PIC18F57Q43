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
    
inicio:
    movlw 81H		    ;cargo 36H en registro Wreg
    movwf LATD, 1	    ;muevo contenido de Wreg hacia RD
    bra inicio
    
    end upcino


