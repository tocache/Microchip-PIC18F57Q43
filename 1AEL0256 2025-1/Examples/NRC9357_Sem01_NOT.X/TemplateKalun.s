;este es un comentario
;PROGRAMA DE NEGADOT LOGICO DE UN BIT
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
    
    
inicio:		    ;Funcionamiento de la aplicacion
    
    bra inicio
    
    end upcino




