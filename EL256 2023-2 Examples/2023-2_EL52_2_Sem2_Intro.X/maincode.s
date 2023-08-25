    PROCESSOR 18F57Q43		    ;Directiva de seleccion del uC
    ;Llamado a cabecera
    #include "cabecera.inc"	    
    
    PSECT upcino, class=CODE, reloc=2, abs	;Declaracion del program section
upcino:						;Etiquete del program section
    ORG 000000H		;Vector de RESET
    bra configuro	;salto a etiqueta configuro
    
    ORG 000020H		;Zona de programa de usuario
configuro:
    ;Configuraciones iniciales de la aplicacion
    ;Configurar el HFINTOSC para 4MHz hacia el CPU
    ;OSCFRQ=02H,OSCCON1=60H,OSCEN=40H
    movlb 0H		;al Bank0 para acceder a los registros de OSC
    movlw 02H		;coloco 02H al Wreg
    movwf OSCFRQ, 1	;muevo Wreg hacia registro OSCFRQ
    movlw 60H		;coloco 60H al Wreg
    movwf OSCCON1, 1	;muevo Wreg hacia registro OSCCON1
    movlw 40H		;coloco 40H en Wreg
    movwf OSCEN, 1	;muevo Wreg hacia registro OSCEN
    
    ;Configurar las E/S de la aplicación
    movlb 4H		;cambio al Bank4
    bsf TRISB, 4, 1	;puerto RB4 sea entrada
    bcf ANSELB, 4, 1	;puerto RB4 como digital
    bsf WPUB, 4, 1	;puerto RB4 con 
    bcf TRISF, 3, 1	;puerto RF3 como salida
    bcf ANSELF, 3, 1	;puerto RF3 como digital
    
inicio:			;Programa de la aplicacion
    btfsc PORTB, 4, 1	;Pregunto si RB4 es cero (pulse el boton)
    bra nopulsaste	;Salta aqui cuando es falso
    bra sipulsaste	;Salta aca cuando es verdadero
    
nopulsaste:
    bcf LATF, 3, 1	;RF3 a cero (se enciende el LED)
    bra inicio		;Salta a inicio
    
sipulsaste:
    bsf LATF, 3, 1	;RF3 a uno (se apaga el LED)
    bra inicio		;Salta a inicio
    
    end upcino		;Cierre del program section
    
    

