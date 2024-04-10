;Este es un comentario
    PROCESSOR 18F57Q43		;Directiva de procesador
    #include "cabecera.inc"	;Llamado al archivo cabecera
    
    PSECT upcino, class=CODE, reloc=2, abs	;Declaración del program section
upcino:						;Abrimos el PSECT
    ORG 000000H					;vector de RESET
    bra configuro				;salto a label configuro
    
    ORG 000100H					;Zona de la aplicación
configuro:
    movlb 00H					;nos vamos al BANK0
    ;Configuracion de la fuente de reloj
    movlw 60H
    movwf OSCCON1, 1				;NOSC 110 (HFINTOSC), NDIV 0000 (1:1)
    movlw 02H
    movwf OSCFRQ, 1				;FRQ 0010 (HFINTOSC a 4MHz)
    bsf OSCEN, 6, 1				;HFOEN = 1 (HFINTOSC encendido)
    movlb 04H					;nos vamos al BANK4
    ;Configuracion de las E/S: RE0 digital input, RF0 digital output
    bsf TRISE, 0, 1				;RE0 es entrada
    bcf ANSELE, 0, 1				;RE0 como digital
    bcf TRISF, 0, 1				;RF0 es salida
    bcf ANSELF, 0, 1				;RF0 como digital

inicio:
    btfsc PORTE, 0, 1				;Pregunto si RE0 es uno
    bra falso					;Cuando es falso
    bra verdad					;Cuando es verdad
    
falso:						;Si es falso RF0 es uno
    bcf LATF, 0, 1				;RF0=1
    bra inicio					;Regreso al inicio
    
verdad:						;Si es cierto RF0 es cero
    bsf LATF, 0, 1				;RF0=0
    bra inicio					;Regreso al inicio    

    ;Cerramos el program section upcino    
    end upcino
    
    
   


