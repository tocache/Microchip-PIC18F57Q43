;Este es un comentario
;Mi primer programa
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;vector de reset
    bra configuro   ;salto a configuro
    
    ORG 000100H	    ;zona de usuario
configuro:
    ;Fuente de reloj HFINTOSC a 4MHz
    movlb 0H	    ;cambio a Bank0
    movlw 60H
    movwf OSCCON1, 1   ;NOSC a HFINTOSC, NDIV a 1:1
    movlw 02H
    movwf OSCFRQ, 1    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1    ;arrancamos el HFINTOSC
    ;Config de las E/s
    movlb 4H		;cambio a Bank4
    bsf TRISF, 4, 1	;RF4 como entrada
    bcf ANSELF, 4, 1	;RF4 como digital
    bcf TRISB, 3, 1	;RB3 como salida
    bcf ANSELB, 3, 1	;RB3 como digital
    
inicio_NOT:
    btfss PORTF, 4, 1	;Pregunto si RF4=1
    bra falsazo		;Falso, salto a falsazo
    bcf LATB, 3, 1	;Verdad, RB3=0
    bra inicio_NOT	;Regreso a inicio_NOT
falsazo:
    bsf LATB, 3, 1	;RB3=1
    bra inicio_NOT	;Regreso a inicio_NOT

    end upcino
    
    


