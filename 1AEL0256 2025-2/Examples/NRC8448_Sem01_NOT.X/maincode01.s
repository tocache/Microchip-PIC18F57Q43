    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 0000000H	    ;vector de reset
    bra configuro	    ;salto a etiqueta configuro
    
    ORG 000100H
configuro:
    ;configuracion de la fuente de reloj:
    movlb 0H		    ;me voy al Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;OSCCON1 = 60H
    movlw 02H
    movwf OSCFRQ, 1	    ;OSCFRQ = 02H
    movlw 40H
    movwf OSCEN, 1	    ;OSCEN = 40H
    ;configuracion de las E/S:
    movlb 04H		    ;me voy al Bank4
    bsf TRISA, 0, 1	    ;RA0 como entrada
    bcf ANSELA, 0, 1	    ;RA0 como digital
    bcf TRISD, 0, 1	    ;RD0 como salida
    bcf ANSELD, 0, 1	    ;RD0 como digital
    
;recien aqui vamos a detallar el funcionamiento de la NOT    
inicio:
    btfss PORTA, 0, 1	    ;pregunto si RA0 es uno
    bra falsaso		    ;falso, salta a etiqueta falsaso
    bra veritas		    ;verdad, salta a etiqueta veritas
    
falsaso:
    bsf LATD, 0, 1	    ;RD0 es uno
    bra inicio		    ;regreso a preguntar

veritas:
    bcf LATD, 0, 1	    ;RD0 es cero
    bra inicio		    ;regreso a preguntar
    
    end upcino

