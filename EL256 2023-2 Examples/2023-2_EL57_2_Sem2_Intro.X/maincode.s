    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT principal, class=CODE, reloc=2, abs	;Apertura del program section
principal:
    ORG 000000H		;Vector de reset (direcciones de mem de prog)
    bra configuro	;Salto a label configuro
    
    ORG 000020H		;Zona de programa de usuario
configuro:
    ;Aquí se colocan las configuraciones iniciales de la aplicación
    ;Configuración de la fuente de reloj del CPU
    ;OSCCON1 = 60H, OSCFRQ = 02H, OSCEN = 40H ->HFINTOSC a 4MHz y al CPU y perif
    movlb 0H		;voy al Bank 0
    movlw 60H		;muevo 60H a Wreg
    movwf OSCCON1, 1	;muevo Wreg hacia reg OSCCON1
    movlw 02H		;muevo 02H a Wreg
    movwf OSCFRQ, 1	;muevo Wreg hacia reg OSCFRQ
    movlw 40H		;muevo 40H a Wreg
    movwf OSCEN, 1	;muevo Wreg hacia reg OSCEN
    ;Configuracion de las E/S
    movlb 4H		;voy al Bank 4
    bsf TRISB, 4, 1	;RB4 como entrada
    bcf ANSELB, 4, 1	;RB4 como digital
    bsf WPUB, 4, 1	;RB4 pullup activado
    bcf TRISF, 3, 1	;RF3 como salida
    bcf ANSELF, 3, 1	;RF3 como digital
    
inicio:
    ;Aqui va el programa de usuario
    btfsc PORTB, 4, 1	;pregunto si RB4 es cero
    bra noescierto	;aqui salta cuando es falso
    bra siescierto	;aqui salta cuando es verdadero
    
noescierto:
    bcf LATF, 3, 1	;RF3 a cero (LED se encienda)
    bra inicio		;retorna a inicio
    
siescierto:
    bsf LATF, 3, 1	;RF3 a uno (LED se apague)
    bra inicio		;retorna a inicio

    end principal	;Fin del program section
    


