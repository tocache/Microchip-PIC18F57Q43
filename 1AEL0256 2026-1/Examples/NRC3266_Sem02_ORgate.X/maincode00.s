;Este es un comentario
    ;Seleccion del CPU
    PROCESSOR 18F57Q43
    ;Llamado a la cabecera
    #include "cabecera.inc"
    
    ;Creacion del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    
    ORG 000000H	    ;Vector de RESET
    bra configuro   ;salto a label configuro
    
    ORG 000100H	    ;Zona de programa de usuario
configuro:
    ;conf el modulo de oscilador
    movlb 0H	    ;Al bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;conf las Entradas/Salidas
    movlb 4H
    setf TRISE, 1	;Todo RE como entradas
    movlw 0FCH
    movwf ANSELE, 1	;RE1 y RE0 como digitales
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital
    
inicio:
    btfsc PORTE, 0, 1	;Pregunto si RE0 es cero
    bra es_falso	;falso, salta a label es_falso
    btfsc PORTE, 1, 1	;verdad y pregunta si RE1 es cero
    bra es_falso	;falso y salta a label es_falso
    bcf LATF, 0, 1	;verdad y RF0=0 (LED off)
    bra inicio		;salto a label inicio
es_falso:
    bsf LATF, 0, 1	;RF0=1 (LED on)
    bra inicio		;salto a label inicio

    end upcino


