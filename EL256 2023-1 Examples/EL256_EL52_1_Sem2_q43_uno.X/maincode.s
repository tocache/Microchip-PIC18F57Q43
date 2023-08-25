    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    goto configuro
    
    ORG 000020H
configuro:
    ;Aqui van las configuraciones iniciales de la app
    movlb 0H		    ;BSR al bank 0
    movlw 60H
    movwf OSCCON1	    ;HFINTOSC con divisor 1:1
    movlw 02H
    movwf OSCFRQ	    ;HFINTOSC a 4MHz
    bsf OSCEN, 6	    ;HFINTOSC habilitado
    ;configuracion de los puertos
    movlb 4H		    ;BSR al bank 4
    bcf TRISD, 0	    ;RD0 como salida
    bcf ANSELD, 0	    ;RD0 como digital
    bcf TRISF, 0	    ;RF0 como salida
    bcf ANSELF, 0	    ;RF0 como digital
    bsf TRISB, 4	    ;RB4 como entrada
    bcf ANSELB, 4	    ;RB4 como digital
    bsf WPUB, 4		    ;pullup del RB4 habilitado
    bcf LATD, 0		    ;RD0 apagado
    bcf LATF, 0		    ;RF0 apagado
    movlb 0H		    ;BSR al bank 0
inicio:
    btfsc PORTB, 4	    ;pregunto si presione boton
    goto inicio		    ;aun no he pulsado
    bsf LATF, 0		    ;enciendo RF0
aunno1:
    btfss PORTB, 4	    ;pregunto si solte el boton
    goto aunno1
aunno2:    
    btfsc PORTB, 4	    ;pregunto si presione boton
    goto aunno2		    ;aun no he pulsado
    bsf LATD, 0		    ;enciendo RD0
aunno3:
    btfss PORTB, 4	    ;pregunto si solte el boton
    goto aunno3
aunno4:    
    btfsc PORTB, 4	    ;pregunto si presione boton
    goto aunno4		    ;aun no he pulsado
    bcf LATF, 0		    ;apago RF0
    bcf LATD, 0		    ;apago RD0
aunno5:
    btfss PORTB, 4	    ;pregunto si solte el boton
    goto aunno5
    goto inicio
    end upcino
    


