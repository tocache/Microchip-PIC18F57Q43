    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    movlb 0H	    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    movlb 4H	    ;al Bank4
    clrf TRISD, 1	;RD como salida
    clrf ANSELD, 1	;RD como digital
    
inicio:
    movlw 36H		;muevo literal 36H a Wreg
    movwf LATD, 1	;muevo contenido de Wreg hacia registro LATD
    bra inicio
    
    end upcino
    
    


