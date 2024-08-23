;Este es un comentario, hola mundo
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
;Creación del program section
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;Vector de RESET
    bra configuro	;salto a label configuro
    
    ORG 000100H		;zona de programa de usuario
configuro:
    ;configurando la fuente de reloj
    movlb 0H		;me voy al Bank0
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 60H
    movwf OSCCON1, 1	;NOSC a HFINTOSC, NDIV 1:1
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configuracion de las E/S
    movlb 4H		;me voy al Bank4
    bsf TRISF, 1, 1	;RF1 como entrada
    bcf ANSELF, 1, 1	;RF1 como digital
    bcf TRISE, 1, 1	;RE1 como salida
    bcf ANSELE, 1, 1	;RE1 como digital
    
inicio_NOT:
    btfss PORTF, 1, 1	;Pregunto si RF1=1
    bra falsazo		;FALSO, salto a label falsazo
    bcf LATE, 1, 1	;VERDAD, RE1 = 0
    bra inicio_NOT	;salto a inicio_NOT
falsazo:
    bsf LATE, 1, 1	;RE1 = 1
    bra inicio_NOT	;salto a inicio_NOT
    end upcino 
    


