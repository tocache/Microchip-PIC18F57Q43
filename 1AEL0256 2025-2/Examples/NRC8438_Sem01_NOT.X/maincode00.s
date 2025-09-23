    ;Directiva de procesador, para indicarle el modelo al compilador
    PROCESSOR 18F57Q43
    ;Llamada al archivo de cabecera
    #include "cabecera.inc"
    
    ;Crear una sección de programa (PSECT)
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;posicion de memoria de programa: VECTOR DE RESET
    bra configuro	;salto a etiqueta configuro
    
    ORG 000100H		;posicion de memoria de programa 100H
configuro:
    ;configurar la fuente de reloj
    movlb 0H		;me voy al BANK0
    movlw 60H
    movwf OSCCON1, 1	;NOSC->HFINTOSC, NDIV->1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configurar las E/S
    movlb 4H		;me voy al BANK4
    bsf TRISA, 0, 1	;RA0 como entrada
    bcf ANSELA, 0, 1	;RA0 como digital
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital
    
inicio:
    btfss PORTA, 0, 1	;Pregunto si RA0 es uno
    bra esfalso		;es falso, salta a etiqueta esfalso
    bra esverdadero	;es verdadero, salta a etiqueta esverdadero
esfalso:
    bsf LATD, 0, 1	;RD0 es uno
    bra inicio		;regreso a preguntar RA0
esverdadero:
    bcf LATD, 0, 1	;RD0 es cero
    bra inicio		;regreso a preguntar RA0
    
    end upcino		;cierre del program section upcino

