    ;Modelo del CPU empleado en el proyecto
    PROCESSOR 18F57Q43
    
    ;Llamado al archivo cabecera (bits de conf)
    #include "cabecera.inc"
    
    ;Declaracion de una seccion de programa
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;pos de memoria de prog = vector de reset
    bra configuro   ;salto a zona de conf de la aplicacion
    
    ORG 000100H	    ;zona de programa de usuario
configuro:
    ;configuracion de la fuente de reloj del micro
    movlb 0h		;Me voy al BANK0
    movlw 60H
    movwf OSCCON1,1	;NOSC=HFINTOSC NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	;FRQ=4MHz
    movlw 40H
    movwf OSCEN, 1	;habilitamos el HFINTOSC
    ;configuracion de las E/S
    movlb 4h		;Me voy al BANK4
    bsf TRISF, 0, 1	;RF0 es entrada
    bcf ANSELF, 0, 1	;RF0 es digital
    bcf TRISE, 0, 1	;RE0 es salida
    bcf ANSELE,0, 1	;RE0 es digital

inicio:
    btfss PORTF, 0, 1	;pregunta si RF0 es uno
    bra esfalso		;viene aqui cuando es falso
    bra esverdad	;viene aqui cuando es verdadero

esfalso:
    bsf LATE, 0, 1	;salida RE0 es uno
    bra inicio		;vuelvo a inicio
    
esverdad:
    bcf LATE, 0, 1	;salida RE0 es cero
    bra inicio		;vuelvo a inicio
    
    end upcino