;Este es un comentario
;Este proyecto es un negador lógico de un bit
;RC0 es la entrada digital, RE1 es la salida digital
    
    PROCESSOR 18F57Q43	    ;modelo de CPU
    ;llamada a la cabecera
    #include "cabecera.inc"
    
    ;Creación de un program section:
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ;empieza el código fuente
    ORG 000000H	    ;vector de RESET
    bra configuro
    
    ORG 000100H	    ;Zona de programa de usuario
configuro:
    ;Configuracion de fuente de reloj para que funcione el CPU
    ;Vamos a configuracion el HFINTOSC como fuente de reloj a 4MHZ
    movlb 0H	    ;nos vamos al Bank0
    movlw 60H	    ;HFINTOSC como fuente y divisor a 1:1
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1 ;HFINTOSC trabaja a 4MHz
    bsf OSCEN, 6, 1 ;encendemos el HFINTOSC

    ;Configuracion de las E/S
    movlb 4H	    ;nos vamos al Bank4
    ;RE1 como salida digital (LED)
    bcf TRISE, 1, 1 ;RE1 como salida
    bcf ANSELE, 1, 1	;RE1 como digital
    ;RC0 como entrada digital (BOTON)
    bsf TRISC, 0, 1 ;RC0 como entrada
    bcf ANSELC, 0, 1	;RC0 como digital
    
;Recien aca esta el codigo para el negador lógico
inicio:
    btfss PORTC, 0, 1	;preguntamos si el boton se machucó
    bra nolopresione	;Falso, salta a etiqueta nolopresione
    bra silopresione	;Verdad, salta a label silopresione
    
nolopresione:
    bsf LATE, 1, 1	;encendemos el LED
    bra inicio		;retorna a inicio parapreguntar de nuevo
    
silopresione:
    bcf LATE, 1, 1	;apagamos el LED
    bra inicio		;retorna a inicio parapreguntar de nuevo

    end upcino

