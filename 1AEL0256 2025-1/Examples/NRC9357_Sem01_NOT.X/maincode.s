;este es un comentario
;PROGRAMA DE NEGADORz LOGICO DE UN BIT
;Hecho por Kalun Lau

    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    ;Creacion del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:    
    ORG 000000H	    ;Vector de RESET
    bra configuro   ;Salto a etiqueta configuro
    
    ORG 000100H	    ;Zona donde empezamos a escribir el codigo fuente de la app
configuro:	    ;Configuracion de reloj y de puertos
    ;Conf de la fuente de reloj
    movlb 0H	    ;Me voy al Bank0
    movlw 60H
    movwf OSCCON1, 1   ;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;Conf de los puertos de E/S
    movlb 4H		;nos vamos al Bank4
    ;RF0 como entrada, RE0 como salida
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital
    bcf TRISF, 0, 1	;RF0 como salida
    bcf ANSELF, 0, 1	;RF0 como digital
    
inicio:		    ;Funcionamiento de la aplicacion
    btfss PORTE, 0, 1	;Pregunto si RE0 es uno
    bra falso		;falso, se va a la etiqueta falso
    bra verdadero	;verdadero, se va a la etiqueta verdadero
    
verdadero:
    bcf LATF, 0, 1	;apago el LED
    bra inicio		;retorno a inicio

falso:
    bsf LATF, 0, 1	;enciendo el LED
    bra inicio
    
    end upcino

