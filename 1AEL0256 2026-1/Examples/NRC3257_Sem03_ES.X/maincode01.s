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
    ;condiciones iniciales de operacion
    movlw 69H	    
    movwf LATD, 1	    ;RD con valor 69H
    
inicio:
    btfsc PORTE, 2, 1	    ;pregunto si RE2=0
    bra $-2		    ;rpta falso, salto a la linea anterior
    comf LATD, 1, 1	    ;aplico complemento del puerto D
    btfss PORTE, 2, 1	    ;pregunto si RE2=1
    bra $-2		    ;rpta falso, salto a la linea anterior
    bra inicio		    ;rpta verdad, salto a label inicio
    end upcino




