    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;configuracion de la fuente de reloj
    movlb 0H	    ;me voy al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configuramos las E/S
    movlb 4H	    ;me voy al Bank4
    movlw 0F0H
    movwf TRISD, 1	;RD0 al RD3 como salidas
    movwf ANSELD, 1	;RD0 al RD3 como digitales
    bcf TRISB, 0, 1	;RB0 como salida
    bcf ANSELB, 0, 1	;RB0 como digital
    movlw 0FFH
    movwf TRISF, 1	;Todo el puerto F como entradas
    movlw 0FCH
    movwf ANSELF, 1	;RF0 y RF1 como digitales
    
inicio:
    btfsc PORTF, 0, 1	;pregunta si RF0 es cero
    bra preguntaRF1	;falso y se va a preguntar al RF1
    btg LATB, 0, 1	;bascular RB0
otro1:
    btfss PORTF, 0, 1	;pregunto si RF0 es uno
    bra otro1		;falso, regresa a preguntar
    bra inicio		;verdad, regresa a inicio
preguntaRF1:
    btfsc PORTF, 1, 1	;pregunta sio RF1 es cero
    bra envia05		;falso, salta a etiqueta envia05
    bra envia0A		;verdad, salta a etiqueta envia0A
envia05:
    movlw 05H
    movwf LATD, 1	;manda 05H a puerto D
    bra inicio		;salta a inicio   
envia0A:
    movlw 0AH
    movwf LATD, 1	;manda 0AH a puerto D
    bra inicio		;salta a inicio
    
    end upcino
    

