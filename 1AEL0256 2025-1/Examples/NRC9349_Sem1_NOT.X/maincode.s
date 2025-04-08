;Este es un comentario
;Mi primer programa, compuerta NOT
;RE1 es la salida, RC0 es la entrada
;Hecho por Kalun 07/04/2025
;Se los dedico a mis alumnos de micro

    ;Modelo de CPU para que el XC8 sepa:
    PROCESSOR 18F57Q43
    ;Llamado al archivo de cabecera para que se carguen
    ;los bits de configuración:
    #include "cabecera.inc"
    
    ;Apertura de un program section con etiqueta upcino,
    ;tipo código, para PIC18 y absoluto (un solo program
    ;section)
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;Vector de RESET	aca viene terminando de llamar a los bits de configuracion
    bra configuro   ;Salto a etiqueta configuro
    
    ORG 000100H	    ;Zona donde esta la aplicación
configuro:
    ;Se declaran por ejemplo la conf de las E/S de la app
    ;Tambien se declaran la conf de la fuente de reloj
    ;Vamos primero a declarar la fuente de reloj, porque sino el uC no funk
    movlb 0H	    ;Me voy al Bank0
    movlw 60H
    movwf OSCCON1, 1	;HFINTOSC y CLKDIV en 1:1
    movlw 02H
    movwf OSCFRQ, 1	;el HFINTOSC trabaje a 4MHz hacia el CPU
    bsf OSCEN, 6, 1	;enciende el HFINTOSC
    
    ;Configurar los puertos de la app
    ;RE1 es la salida, RC0 es la entrada
    movlb 4H	;nos vamos al Bank4
    bcf TRISE, 1, 1	;RE1 como salida
    bcf ANSELE, 1, 1	;RE1 como digital
    bsf TRISC, 0, 1	;RC0 como entrada
    bcf ANSELC, 0, 1	;RC0 como dgital
        
;Codigo de la aplicación (del NOT)
inicio:
    btfss PORTC, 0, 1	;Pregunto si RC0 es uno (si presione BTN)
    bra nopresione	;Falso, salto a etiqueta nopresione
    bra sipresione	;Verdad salto a etiqueta sipresione
    
nopresione:
    bsf LATE, 1, 1	;Enciendo el LED
    bra inicio		;Regreso a inicio
    
sipresione:
    bcf LATE, 1, 1	;Apago el LED
    bra inicio		;Regreso a inicio
    
    end upcino
    
    
    


