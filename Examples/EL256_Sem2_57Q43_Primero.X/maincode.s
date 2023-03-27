;Este es un comentario
;Ejemplo hecho por Kalun ps
    PROCESSOR 18F57Q43		    ;modelo de micro
    #include "cabecera.inc"	    ;llamada a cabecera
    
    PSECT upcino, class=CODE, reloc=2, abs  ;program section
upcino:			    ;etiqueta upcino
    ORG 000000H		    ;vector de reset
    goto configuro	    ;salto a etiqueta configuro
    
    ORG 000020H		    ;zona de prog de usuario
configuro:		    ;etiqueta configuro
    ;aqui van los registros de conf para el reloj
    movlb 0H		    ;bank0 al access bank
    movlw 60H
    movwf OSCCON1	    ;HFINTOSC con divisor a 1:1
    movlw 02H
    movwf OSCFRQ	    ;HFINTOSC a 4MHz
    bsf OSCEN, 6	    ;HFINTOSC habilitado
    ;aqui van los registros de conf para las E/S
    movlb 4H		    ;bank4 al access bank    
    bsf TRISB, 4	    ;RB4 como entrada
    bcf ANSELB, 4	    ;RB4 como digital
    bsf WPUB, 4		    ;RB4 activado su pull-up
    bcf TRISF, 3	    ;RF3 como salida
    bcf ANSELF, 3 	    ;RF3 como digital
    
loop:			    ;etiqueta loop
    ;programa de usuario
    btfss PORTB, 4	    ;pregunto si RA0 es uno
    goto nah		    ;F a la preg anterior, salta a etiqueta nah
    bcf LATF, 3		    ;V a la preg anterior, RC0 a cero
    goto loop		    ;salto a etiqueta loop
nah:
    bsf LATF, 3		    ;RC0 a uno
    goto loop		    ;salto a etiqueta loop
    end upcino		    ;fin de program section


