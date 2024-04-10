;Esto es un comentario
    PROCESSOR 18F57Q43			    ;modelo de MCU
    #include "cabecera.inc"		    ;llamado a archivo cabecera
    
    PSECT upcino, class=CODE, reloc=2, abs  ;creación del program section
upcino:					    ;declaracion de PSECT upcino
    ORG 000000H				    ;vector de RESET
    bra configuro			    ;salto a etiqueta configuro
    
    ORG 000100H				    ;Zona de programa de usuario
configuro:
    ;config fuente reloj del MCU
    movlb 0H				    ;Nos vamos al BANK0
    movlw 60H
    movwf OSCCON1			    ;se escoja HFINTOSC y NDIV 1:1
    movlw 02H
    movwf OSCFRQ			    ;HFINTOSC a 4MHz
    bsf OSCEN, 6			    ;HFOEN=1 habilitamos el HFINTOSC
    movlb 4H				    ;Nos vamos al BANK4
    ;config E/S
    bsf TRISE, 0			    ;Puerto RE0 como entrada
    bcf ANSELE, 0			    ;Puerto RE0 como digital
    bcf TRISF, 0			    ;Puerto RF0 como salida
    bcf ANSELF, 0			    ;Puerto RF0 como digital
    
inicio:
    btfss PORTE, 0			    ;pregunta si RE0=1
    bra es_falso			    ;salta cuando es falso
    bra es_verdad			    ;salta cuando es verdad
    
es_falso:    
    bsf LATF, 0				    ;RF0 a uno
    bra inicio				    ;salto a etiqueta inicio
    
es_verdad:
    bcf LATF, 0				    ;RF0 a cero
    bra inicio				    ;salto a etiqueta inicio

    end upcino

