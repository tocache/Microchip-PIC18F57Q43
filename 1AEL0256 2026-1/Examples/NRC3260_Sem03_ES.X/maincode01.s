    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;Vector de RST
    bra configuro	;salto a label configuro
    
    ORG 000100H		;inicio de user program
configuro:
    ;conf modulo de osc
    movlb 0H		;entro a Bank0
    movlw 60H		;cargo 60H a wreg
    movwf OSCCON1, 1	;muevo wreg a OSCCON1
    movlw 02H		;cargo 02Ha wreg
    movwf OSCFRQ, 1	;muevo wreg a OSCFRQ
    movlw 40H		;cargo 40H a wreg
    movwf OSCEN, 1	;muevo wreg a OSCEN
    ;conf e/s
    movlb 4H		;entro a Bank4
    clrf TRISD, 1	;limpio registro TRISD/todo RD como salidas
    clrf ANSELD, 1	;limpio registro ANSELD/todo RD como digitales 
    movlw 0CFH		;cargo 0CFH a wreg
    movwf ANSELF, 1	;muevo wreg a ANSELF/RF4 y RF5 como digitales
    movlw 30H		;cargo 30H a wreg
    movwf WPUF, 1	;muevo wreg a WPUF/RF4 y RF5 pullup enabled
inicio:
    btfsc PORTF, 4, 1	;pregunto si RF4 es cero
    bra es_falso1	;rpta falsa, salta a label es_falso1
    btfsc PORTF, 5, 1	;rpta verdad, pregunta si RF5 es cero
    bra es_falso2	;rpta falsa, salto a label es_falso2
    bra noventaynueve	;rpta verdad, salto a label noventaynueve}
es_falso1:
    btfsc PORTF, 5, 1	;pregunto si RF5 es cero
    bra noventaynueve	;rpta falso, salta a label noventaynueve
    movlw 3CH		;muevo 3CH a wreg
    movwf LATD, 1	;muevo wreg a LATD
    bra inicio		;salto a label inicio
noventaynueve:
    movlw 99H		;muevo 99H a wreg
    movwf LATD, 1	;muevo wreg a LATD
    bra inicio		;salto a label inicio
es_falso2:
    movlw 0C3H		;muevo 0C3H a wreg
    movwf LATD, 1	;muevo wreg a LATD
    bra inicio		;salto a label inicio
    
    end upcino





