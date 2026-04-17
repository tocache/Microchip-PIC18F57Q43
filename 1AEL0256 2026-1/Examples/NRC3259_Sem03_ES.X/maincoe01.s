    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;vector de RST
    bra configuro
    
    ORG 000100H		    ;Zona de user program
configuro:
    ;conf del modulo de oscilador
    movlb 0H		    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf de las E/S
    movlb 4H		    ;Al Bank4
    clrf TRISD, 1	    ;Todo RD como salidas
    clrf ANSELD, 1	    ;Todo RD como digitales
    setf TRISF, 1	    ;RF4 y RF5 entradas
    movlw 0CFH
    movwf ANSELF, 1	    ;RF4 y R5 digitales
    movlw 30H
    movwf WPUF, 1	    ;RF4 y RF5 con pullup enabled

inicio:
    btfsc PORTF, 4, 1	    ;pregunto si RF4 es cero
    bra otro1		    ;rpta falso, salto a label otro1
    btfsc PORTF, 5, 1	    ;pregunto si RF5 es cero
    bra otro3
    bra otro2
otro3:    
    movlw 69H		    ;rpta verdad, muevo 69H a wreg
    movwf LATD, 1	    ;muevo wreg a LATD
    bra inicio		    ;salto a label inicio
otro1:
    btfsc PORTF, 5, 1	    ;pregunto si RF5 es cero
    bra otro2		    ;rpta falso, salto a label otro2
    movlw 96H		    ;rpta verdad, muevo 96H a wreg
    movwf LATD, 1	    ;muevo wreg a LATD
    bra inicio		    ;salto a label inicio
otro2:
    movlw 0AAH		    ;muevo 0AAH a wreg
    movwf LATD, 1	    ;muevo wreg a LATD
    bra inicio		    ;salto a label inicio
    end upcino





