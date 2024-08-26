;Esta es una aplicación de una compuerta NOT de un bit
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro	;va a saltar a la etiqueta configuro
    
    ORG 000100H		;zona de programa usuario
configuro:
    ;Configuración de la fuente de reloj del PIC18F57Q43
    movlb 0H		;me voy al BANK0
    movlw 60H
    movwf OSCCON1, 1	;fuente de reloj es HFINTOSC y CLKDIV entre 1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC trabaje a 4MHz
    bsf OSCEN, 6, 1	;HFINTOSC habilitado
    ;Configuración de los puertos de E/S
    movlb 4H		;me voy al BANK4
    bsf TRISF, 0, 1	;RF0 es entrada
    bcf ANSELF, 0, 1	;RF0 es digital
    bcf TRISB, 0, 1	;RB0 es salida
    bcf ANSELB, 0, 1	;RB0 como digital
inicio_compuerta_not:
    btfss PORTF, 0, 1	;Pregunta si RF0 es uno
    bra falso		;Falso, salto a etiqueta falso
    bcf LATB, 0, 1	;Verdad, apago LED en RB0
    bra inicio_compuerta_not	;Salto a inicio
falso:
    bsf LATB, 0, 1	;enciendo LED en RB0
    bra inicio_compuerta_not	;Salto a inicio
    
    end upcino


