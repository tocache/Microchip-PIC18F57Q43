    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;vector de reset
    bra configuro	    ;salto a label configuro
    
configuro:		    ;label configuro
    movlb 0H		    ;al BANK0
    movlw 60H
    movwf OSCCON1, 1	    ;HFINTOSC y 1:1
    movlw 03H
    movwf OSCFRQ, 1	    ;HFINTOSC a 8MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC habilitado
    movlb 4H		    ;al BANK4
    bsf TRISD, 2, 1	    ;RD2 como entrada
    bcf ANSELD, 2, 1	    ;RD2 como digital
    bcf TRISF, 1, 1	    ;RF1 como salida
    bcf ANSELF, 1, 1	    ;RF1 como digital
    bcf TRISF, 2, 1	    ;RF2 como salida
    bcf ANSELF, 2, 1	    ;RF2 como digital
    bcf LATF, 1, 1	    ;RF1 en cero
    bcf LATF, 2, 1	    ;RF2 en cero
inicio:
    btfss PORTD, 2, 1	    ;pregunto si presione el boton
    bra inicio		    ;falso, no presione el boton y vuelvo a preguntar
    bsf LATF, 1, 1	    ;verdad, enciendo primer LED
otro1:
    btfsc PORTD, 2, 1	    ;pregunto si deje de presional el boton
    bra otro1		    ;falso y vuelvo a preguntar
otroa1:
    btfss PORTD, 2, 1	    ;pregunto si presione el boton
    bra otroa1
    bcf LATF, 1, 1	    ;verdad, apago el LED
otroa2:
    btfsc PORTD, 2, 1	    ;pregunto si solte el boton
    bra otroa2
otro2:
    btfss PORTD, 2, 1	    ;pregunto si presione el boton
    bra otro2		    ;falso, no presione el boton y vuelvo a preguntar
    bsf LATF, 2, 1	    ;verdad, enciendo primer LED
otro3:
    btfsc PORTD, 2, 1	    ;pregunto si deje de presional el boton
    bra otro3		    ;falso y vuelvo a preguntar
otroa3:
    btfss PORTD, 2, 1	    ;pregunto si pulse el boton
    bra otroa3
    bcf LATF, 2, 1	    ;verdad, apago el LED
otroa4:
    btfsc PORTD, 2, 1	    ;pregunto si deje de presionar el boton
    bra otroa4
    bra inicio		    ;regreso a label inicio
    
    end upcino
    