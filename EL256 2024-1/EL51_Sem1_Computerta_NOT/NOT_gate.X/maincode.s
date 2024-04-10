;Este es un comentario
;Programa para emular una compuerta NOT
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    
    ORG 000000H		;Vector de reset
    bra configuro	;Salto a la zona de conf de la app
    
    ORG 000020H
configuro:		;Zona de conf de la app    
    ;Configuracion de la fuente de reloj del micro
    movlb 0H		;Voy al BANK0
    movlw 60H
    movwf OSCCON1	;Fuente de reloj en HFINTOSC y CLKDIV 1:1
    movlw 02H
    movwf OSCFRQ	;HFINTOSC esta a 4MHz
    movlw 40H
    movwf OSCEN		;Habilitamos HFINTOSC
    movlb 4H		;Pasamos al BANK4
    ;Configuracion de las I/O o E/S
    ;RB4 sea entrada digital con pullup activado
    bsf TRISB, 4	;TRISB4 debe de ser uno para que sea entrada
    bcf ANSELB, 4	;ANSELB4 debe de ser cero para que sea digital
    bsf WPUB, 4		;WPUB4 debe de ser uno para que se active la pullup
    ;RF3 sea salida digital
    bcf TRISF, 3	;TRISF3 debe de ser cero para que sea salida
    bcf ANSELF, 3	;ANSELF3 debe de ser cero para que sea digital

inicio:
    ;Leo el RB4
    btfsc PORTB, 4	;Pregunto si RB4=0
    bra falso		;Viene aqui si es falso, salta a label falso
    bsf LATF, 3		;Viene aqui si es cierto, RF3=1
    bra inicio		;Salta a label inicio
falso:    
    bcf LATF, 3		;RF3=0
    bra inicio		;Salta a label inicio
    
    end upcino
    

