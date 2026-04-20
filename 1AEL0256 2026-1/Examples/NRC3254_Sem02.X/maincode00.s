;Este es un comentario
    ;directiva para establecer el CPU
    PROCESSOR 18F57Q43
    ;llamada al archivo cabecera.inc
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;vector de RESET
    bra al_configuro	;salto a label al_configuro

    ORG 000100H
al_configuro:
    ;conf del modulo de oscilador
    movlb 0H	    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;conf de las E/S
    movlb 4H	    ;al Bank4
    movlw 0FFH
    movwf TRISC, 1	;RC1 y RC0 como entradas
    movlw 0FCH
    movwf ANSELC, 1	;RC1 y RC0 como digitales
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital
    
inicio:
    btfss PORTC, 0, 1	;pregunto si RC0=1
    bra al_falso	;falso, salta a label al_falso
    btfss PORTC, 1, 1	;verdad y pregunta si RC1=1
    bra al_falso	;falso, salta a label al_falso
    bcf LATF, 0, 1	;verdad, RF0=0 o LED apagado
    bra inicio		;salta a label inicio
al_falso:
    bsf LATF, 0, 1	;RF0=1 o LED encendido
    bra inicio		;salta a label inicio
    


