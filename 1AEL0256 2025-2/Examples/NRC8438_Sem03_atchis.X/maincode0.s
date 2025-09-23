    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf la fuente de reloj
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf las E/S
    movlb 4H
    movlw 0F0H
    movwf TRISD, 1	    ;RD0 al RD3 como salidas
    movwf ANSELD, 1	    ;RD0 al RD3 como digitales
    bcf TRISB, 0, 1	    ;RB0 como salida
    bcf ANSELB, 0, 1	    ;RB0 como digital
    setf TRISF, 1	    ;Todo el puerto F como entradas
    movlw 0FCH
    movwf ANSELF, 1	    ;RF1 y RF0 como digitales
    movlw 03H
    movwf WPUF, 1	    ;RF1 y RF0 con pullup activadas

inicio:    
    btfsc PORTF, 0, 1	    ;Pregunto si RF0 es cero (si presione el boton1)
    bra preguntaRF1	    ;falso, salta a etiqueta pregunta RF1
    btg LATB, 0, 1	    ;verdad, aplico complemento a RB0
otro1:
    btfss PORTF, 0, 1	    ;Pregunto si RF0 es uno (si solte el boton1)
    bra otro1		    ;falso, regresa a pregunta si RF0=1
    bra inicio		    ;verdad, regresa a inicio
preguntaRF1:
    btfsc PORTF, 1, 1	    ;Pregunto si RF1 es cero (si presione el boton2)
    bra imprime5	    ;falso, salta a label imprime5
    movlw 0AH		    ;verdad, a imprimir A en RD
    movwf LATD, 1	    
    bra inicio		    ;regresa a inicio
imprime5:
    movlw 05H		    ;imprimir 5 en RD
    movwf LATD, 1	    
    bra inicio		    ;regresa a inicio
    
    end upcinos
    
