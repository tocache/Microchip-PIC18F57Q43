;Este es un comentario
;Este código es para emular una compuerta NOT de un bit
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;Vector de RESET
    bra configuro	;Salto a zona de configuracion de app
    
    ORG 000100H		;Zona de programa de la app
configuro:    
    ;Configurar la fuente de reloj del CPU
    ;Se va a utilizar el HFINTOSC a 4MHz
    movlb 0H		;Nos vamos al BANK0
    movlw 60H
    movwf OSCCON1	;Fuente HFINTOSC y CLKDIV 1:1
    movlw 02H
    movwf OSCFRQ	;HFINTOSC a 4MHz
    bsf OSCEN, 6	;Habilitando el HFINTOSC
    ;Configurar los puertos de E/S
    movlb 4H		;Nos vamos al BANK4
    ;RB4 como entrada digital y pullup activado
    bsf TRISB, 4	;RB4 es una entrada
    bcf ANSELB, 4	;RB4 es digital
    bsf WPUB, 4		;RB4 tiene pullup
    ;RF3 como salida digital
    bcf TRISF, 3	;RF3 es una salida
    bcf ANSELF, 3	;RF3 es digital
    
inicio:    
    btfsc PORTB, 4	;Leo el puerto y pregunto si RB4=0
    bra falso		;Salta aqui cuando es falso
    bsf LATF, 3		;Si es cierto RF3=1
    bra inicio		;Salta a inicio
falso:
    bcf LATF, 3		;RF3=0
    bra inicio		;Salta a inicio
    
    end upcino