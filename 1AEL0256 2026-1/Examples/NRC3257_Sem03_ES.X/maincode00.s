    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;Vector RST
    bra configuro
    
    ORG 000100H		    ;zona de user program
configuro:    
    ;conf modulo oscilador
    movlb 0H		    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf E/S
    movlb 4H
    clrf TRISD, 1	    ;RD todos salidas
    clrf ANSELD, 1	    ;RD todos digitales
    bsf TRISE, 2, 1	    ;RE2 entrada
    bcf ANSELE, 2, 1	    ;RE2 digital
    bsf WPUE, 2, 1	    ;RE2 pullup enabled

inicio:
    movlw 0D3H		    ;muevo 0D3H a Wreg
    movwf LATD, 1	    ;muevo Wreg a LATD (puerto RD)
    bra inicio
    
    end upcino

