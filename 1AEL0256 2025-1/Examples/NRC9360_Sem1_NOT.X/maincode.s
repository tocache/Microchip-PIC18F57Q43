;Este es un comentario, programa para compuerta NOT
;Hecho por Kalun
    
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;Vector de reset
    bra configuro   ;salto a label configuro
    
    ORG 000100H	    ;zona de programa de usuario
configuro:
    ;Aqui se va a configurar la fuente de reloj
    movlb 0H	    ;nos vamos al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;Aqui se va a configurar los puertos de E/S
    movlb 4H		;nos vamos al Bank4
    ;Para RB2:
    bsf TRISB, 2, 1	;RB2 como entrada
    bcf ANSELB, 2, 1	;RB2 como digital
    ;Para RC1:
    bcf TRISC, 1, 1	;RC1 como salida
    bcf ANSELC, 1, 1	;RC1 como digital
    
inicio:
    btfss PORTB, 2, 1	;Pregunto si RB2 es uno, si presione el boton
    bra noescierto	;Falso, salto a label noescierto
    bra siescierto	;Verdad, salto a label siescierto
    
noescierto:
    bsf LATC, 1, 1	;RC1=1, enciendo el LED
    bra inicio		;retorno a label inicio

siescierto:    
    bcf LATC, 1, 1	;RC1=0, apago el LED
    bra inicio		;retorno a inicio
    end upcino


