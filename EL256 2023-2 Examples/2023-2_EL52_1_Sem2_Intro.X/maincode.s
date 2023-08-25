    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;Vector RESET
    bra configuro   ;Salto a label configuro
    
    ORG 000020H	    ;Zona de programa de usuario
configuro:
    ;Todas las configuraciones necesarias para que funcione la aplicacion
    
    ;Configuracion de la fuente de reloj del CPU y perifericos
    ;OSCCON1=60H,OSCFRQ=02H,OSCEN=40H para HFINTOSC a 4MHZ hacia el CPU y perifs.
    movlb 0H		;me voy al Bank 0
    movlw 60H		;cargando 60H al Wreg
    movwf OSCCON1, 1	;moviendo Wreg hacia registro OSCCON1
    movlw 02H		;cargando 02H hacia Wreg
    movwf OSCFRQ, 1	;moviendo Wreg hacia registro OSCFRQ
    movlw 40H		;cargando 40H hacia Wreg
    movwf OSCEN, 1	;moviendo Wreg hacia registro OSCEN
    
    ;Configuracion de los periféricos y las E/S
    movlb 4H		;nos vamos al Bank 4
    bsf TRISB, 4, 1	;puerto RB4 como entrada
    bcf ANSELB, 4, 1	;puerto RB4 como digital
    bsf	WPUB, 4, 1	;puerto RB4 con pullup activado
    bcf TRISF, 3, 1	;puerto RF3 como salida
    bcf ANSELF, 3, 1	;puerto RF3 digital
    
inicio:
    btfsc PORTB, 4, 1	;pregunto si RB4 es cero
    bra noescierto	;cuando es falso, salta a etiqueta noescierto
    bra siescierto	;cuando es verdad, salta a etiqueta siescierto

noescierto:
    bcf LATF, 3, 1	;puerto RF3 a cero (LED encendido)
    bra inicio		;Salto a label inicio
    
siescierto:
    bsf LATF, 3, 1	;puerto RF4 a uno (LED apagado)
    bra inicio		;salto a label inicio
    
    end upcino


